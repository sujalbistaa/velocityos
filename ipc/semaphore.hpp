#pragma once

#include <cstdint>
#include <atomic>

namespace vos::ipc {

/**
 * @class Semaphore
 * @brief A counting semaphore for inter-task synchronization.
 *
 * This class provides a standard counting semaphore. It is built using
 * C++ atomic operations to ensure thread safety without needing to disable
 * interrupts for simple operations.
 */
class Semaphore {
public:
    /**
     * @brief Constructs a semaphore.
     * @param initial_count The initial count of the semaphore.
     * @param max_count The maximum count the semaphore can hold.
     */
    Semaphore(uint32_t initial_count, uint32_t max_count = 0xFFFFFFFF)
        : count_(initial_count), max_count_(max_count) {}

    // Disable copy/move semantics.
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    /**
     * @brief Acquires (takes or pends on) the semaphore.
     *
     * If the semaphore count is greater than zero, it is decremented and the
     * function returns immediately. If the count is zero, the calling task
     * will be blocked until the semaphore is released.
     *
     * @param timeout_ms Timeout in milliseconds to wait. 0 means wait forever.
     * @return True if the semaphore was acquired, false on timeout.
     */
    bool acquire(uint32_t timeout_ms = 0);

    /**
     * @brief Releases (gives or posts) the semaphore.
     *
     * Increments the semaphore count. If any tasks are blocked waiting for
     * the semaphore, the highest priority waiting task is unblocked.
     */
    void release();

private:
    std::atomic<uint32_t> count_;
    const uint32_t max_count_;
    // In a real implementation, a waiting list of tasks would be here.
    // e.g., vos::core::TaskControlBlock* waiting_list_head_;
};

} // namespace vos::ipc
