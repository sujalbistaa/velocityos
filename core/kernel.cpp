#include "core/kernel.hpp"
#include "core/task.hpp"
#include "sched/scheduler.hpp"

#include <vector> // Required for std::vector

namespace vos::core {

// Global list of statically created tasks. In a real system, this might
// be located in a specific memory section.
// Note: Using std::vector here is for simplicity during setup. In a real-time
// system, you would likely use a statically allocated array or a custom list.
static std::vector<Task*> g_task_list;
static sched::Scheduler g_scheduler;

/**
 * @brief Initializes the VelocityOS kernel.
 *
 * This function should be called once at startup. It initializes the scheduler,
 * registers all statically defined tasks, and sets up the system tick timer.
 */
void kernel_init() {
    // In a real implementation, this would configure the hardware timer (e.g., SysTick).
    // For now, we just prepare the scheduler.
    g_scheduler.initialize();

    // Register all tasks with the scheduler.
    for (auto* task : g_task_list) {
        g_scheduler.add_task(task->get_tcb());
    }
}

/**
 * @brief Starts the VelocityOS kernel and the scheduler.
 *
 * This function starts the first task and begins the scheduling process.
 * It should never return.
 */
void kernel_start() {
    // This will trigger the first context switch and start the highest priority task.
    g_scheduler.start();

    // This point should never be reached.
    while (1);
}

/**
 * @brief Statically registers a task with the kernel.
 *
 * This is a helper function to allow tasks to be defined before the kernel is
 * initialized.
 *
 * @param task Pointer to the task to register.
 */
void register_static_task(Task* task) {
    g_task_list.push_back(task);
}

} // namespace vos::core
