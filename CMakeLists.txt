# Step 1: Basic Project Setup
cmake_minimum_required(VERSION 3.16)
project(VelocityOS_Blinky CXX C)

# Step 2: Set the C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Step 3: Tell the compiler where to find header files (*.hpp)
# This is the most important part to fix your errors.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Step 4: Define our one and only program: blinky_task
add_executable(blinky_task
    # List all the .cpp files needed for this program
    examples/blinky_task.cpp
    core/kernel.cpp
    core/task.cpp
    sched/scheduler.cpp
)

# Step 5: Print a success message
message(STATUS "Successfully configured the simple Blinky project!")
