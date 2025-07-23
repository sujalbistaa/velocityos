#include "core/kernel.hpp"
#include "core/task.hpp"

// Assume a simple HAL for GPIO exists.
// #include "hal/gpio.hpp"

// --- Task Definition ---

// Define a task function for blinking an LED.
void blinky_led_task_fn(void* params) {
    // In a real scenario, we would get a GPIO object from params or a global registry.
    // hal::Gpio led(PORTA, PIN5);
    // led.set_mode(hal::GpioMode::Output);

    while (1) {
        // led.toggle();
        
        // This is where we would call a kernel delay function.
        // For now, it's a placeholder comment.
        // vos::core::task_delay_ms(500);
        
        // A busy-wait loop for simulation purposes.
        for (volatile int i = 0; i < 1000000; ++i);
    }
}

// --- Static Task Creation ---

// Statically allocate the task object.
vos::core::Task blinky_task(
    "blinky",               // Task name
    blinky_led_task_fn,     // Task entry function
    nullptr,                // Parameters
    5,                      // Priority
    1024                    // Stack size in bytes
);

// --- Main Application Entry ---

int main() {
    // The application's main function is responsible for initializing
    // the hardware, registering tasks, and starting the kernel.

    // 1. Initialize hardware (clocks, etc.)
    // hardware_init();

    // 2. Register all static tasks with the kernel.
    vos::core::register_static_task(&blinky_task);
    // Register other tasks here...

    // 3. Initialize the kernel. This sets up the scheduler.
    vos::core::kernel_init();

    // 4. Start the kernel. This call does not return.
    vos::core::kernel_start();

    return 0; // Should not be reached.
}
