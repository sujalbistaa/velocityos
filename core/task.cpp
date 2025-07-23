#include "core/task.hpp"
#include <new> // for std::nothrow

namespace vos::core {

Task::Task(const char* name, EntryFunction entry, void* entry_params, uint8_t priority, uint32_t stack_size)
    : entry_function_(entry), entry_params_(entry_params) {
    
    // Allocate stack memory. Using new for simplicity, a real implementation
    // would use a dedicated memory pool.
    stack_ = new (std::nothrow) uint32_t[stack_size / sizeof(uint32_t)];

    // Initialize the TCB
    if (stack_) {
        tcb_.stack_base = stack_;
        tcb_.stack_size = stack_size;
        tcb_.name = name;
        tcb_.priority = priority;
        tcb_.state = TaskState::Suspended; // Task is created but not yet ready
        tcb_.next_tcb = nullptr;

        // Initialize the stack for the context switcher
        initialize_stack();
    } else {
        // Handle stack allocation failure
        // In a real system, this would trigger an assertion or error handler.
    }
}

Task::~Task() {
    delete[] stack_;
}

void Task::initialize_stack() {
    // This is highly architecture-specific (for ARM Cortex-M)
    // The stack pointer will point to the top of the allocated memory.
    uint32_t* sp = tcb_.stack_base + (tcb_.stack_size / sizeof(uint32_t));

    // The ARM Cortex-M architecture expects a specific stack frame to be present
    // when a task starts for the first time. The context switcher (PendSV_Handler)
    // will pop these values off the stack into the CPU registers.

    // The stack must be 8-byte aligned.
    sp = (uint32_t*)((uintptr_t)sp & ~0x7);

    // Initial register values to be "restored" by the first context switch.
    // Order is important and defined by the Cortex-M exception entry sequence.
    *(--sp) = 0x01000000; // xPSR (Thumb state bit set)
    *(--sp) = (uint32_t)entry_function_; // PC (Program Counter)
    *(--sp) = 0; // LR (Link Register) - not critical for task start
    *(--sp) = 0; // R12
    *(--sp) = 0; // R3
    *(--sp) = 0; // R2
    *(--sp) = 0; // R1
    *(--sp) = (uint32_t)entry_params_; // R0 (first argument to the task function)

    // The remaining registers (R4-R11) are also pushed onto the stack.
    *(--sp) = 0; // R11
    *(--sp) = 0; // R10
    *(--sp) = 0; // R9
    *(--sp) = 0; // R8
    *(--sp) = 0; // R7
    *(--sp) = 0; // R6
    *(--sp) = 0; // R5
    *(--sp) = 0; // R4

    // Set the task's stack pointer to the newly prepared top of the stack.
    tcb_.stack_ptr = sp;
}

} // namespace vos::core
