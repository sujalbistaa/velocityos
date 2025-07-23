# VelocityOS - A Lightweight, Distributed RTOS

VelocityOS is a modern, C++17-based Real-Time Operating System designed for high-performance, low-power embedded systems. It is built for ARM Cortex-M microcontrollers and designed with future portability to RISC-V in mind.

## Core Principles

- **Modular:** Components like the scheduler, IPC, and memory management are decoupled.
- **Efficient:** Optimized for low latency and minimal resource footprint, suitable for systems with <= 64KB RAM.
- **Safe:** Written in embedded-safe C++17, minimizing dynamic allocations and avoiding STL overhead.
- **Extensible:** Designed with a clear Hardware Abstraction Layer (HAL) and driver model for easy porting.

## Architecture Overview

VelocityOS follows a standard microkernel architecture. The core is responsible for scheduling, time management, and inter-process communication. Drivers and application-level tasks run on top of this core.

### High-Level Diagram


+-----------------------------------------------------------------+
|                         Application Layer                       |
| (e.g., Sensor Fusion, PID Control, Communication Stacks)        |
+-----------------------------------------------------------------+
|                             IPC Layer                           |
| (Queues, Semaphores, Mutexes, Event Flags, Message Bus)         |
+-----------------------------------------------------------------+
|                            Core Kernel                          |
|                                                                 |
|  +-----------------+  +-----------------+  +------------------+ |
|  | Task Management |  |    Scheduler    |  |  Memory Manager  | |
|  | (TCB, Stacks)   |  | (Pre-emptive)   |  | (Pools, Slabs)   | |
|  +-----------------+  +-----------------+  +------------------+ |
|                                                                 |
+-----------------------------------------------------------------+
|                 Hardware Abstraction Layer (HAL)                |
|           (Cortex-M Core, Timers, GPIO, UART, I2C, SPI)          |
+-----------------------------------------------------------------+
|                             Hardware                            |
|                  (STM32, NXP, TI, etc.)                         |
+-----------------------------------------------------------------+


### Directory Structure


velocityos/
├── core/         # Kernel core, task management, system calls
├── docs/         # Documentation (e.g., task lifecycle)
├── drivers/      # Device drivers (I2C, SPI, UART, etc.)
├── examples/     # Example applications
├── hal/          # Hardware Abstraction Layer for different MCUs
├── ipc/          # Inter-Process Communication mechanisms
├── sched/        # Scheduling algorithms (e.g., pre-emptive, EDF)
├── tests/        # Unit and integration tests
├── tools/        # Debugging scripts, CLI tools
└── README.md


## Getting Started

To get started, you will need an ARM-GCC toolchain. The project uses CMake for building.

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
    cd velocityos
    ```

2.  **Build an example:**
    ```bash
    mkdir build && cd build
    cmake ../examples/blinky_task
    make
    ```

3.  **Flash to your target.**

---
*Copyright (c) 2025, Sujal Bist*
