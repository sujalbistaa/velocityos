#pragma once

#include "core/task.hpp" 

namespace vos::sched {

// Define the maximum number of priority levels.
constexpr int MAX_PRIORITIES = 16;

/**
 * @class Scheduler
 * @brief Manages task scheduling in VelocityOS.
 *
 * This class implements a pre-emptive, priority-based scheduler. It maintains
 * ready lists for each priority level and is responsible for context switching.
 */
class Scheduler {
public:
    Scheduler();

    /**
     * @brief Initializes the scheduler's internal data structures.
     */
    void initialize();

    /**
     * @brief Adds a task to the scheduler's ready list.
     * @param tcb The Task Control Block of the task to add.
     */
    void add_task(core::TaskControlBlock& tcb);

    /**
     * @brief Starts the scheduler and the first task.
     */
    void start();

    /**
     * @brief The main scheduling logic, called from the system tick handler.
     */
    void schedule();

private:
    /**
     * @brief Finds the highest-priority ready task.
     * @return A pointer to the TCB of the next task to run, or nullptr if none.
     */
    core::TaskControlBlock* find_next_task();

    // The currently running task.
    core::TaskControlBlock* current_tcb_;

    // An array of linked lists, one for each priority level.
    core::TaskControlBlock* ready_lists_[MAX_PRIORITIES];
};

} // namespace vos::sched
