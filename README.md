# Project Management & Scheduling System (CPM)

A C++ based Project Management tool that utilizes **Object-Oriented Programming** and **Linked List Data Structures** to calculate project schedules, identify critical paths, and manage resource allocation.

## 📋 Features

- **Automated Scheduling**: Calculates Early Start (ES), Early Finish (EF), Late Start (LS), and Late Finish (LF) for all tasks.
- **Critical Path Analysis**: Identifies "Critical Tasks" (tasks with zero slack) that determine the minimum project duration.
- **Dependency Management**: Allows users to define complex task dependencies and prevents circular dependency logic.
- **Resource Allocation**: Maps specific skills to tasks and calculates completion time based on resource availability.
- **Robust Validation**: Includes specialized handlers to prevent invalid data entry and ensure system stability.

## 🏗️ System Architecture

The project is built using a modular header-only approach (excluding `main.cpp`):

* **Project Controller**: Manages the collection of tasks and resources.
* **CPM Logic**: Implements forward and backward pass algorithms to determine project timelines.
* **Custom Data Structures**: Uses a proprietary template-based Linked List instead of STL containers for educational demonstration of memory management.

## 🚀 Getting Started

### Prerequisites
- A C++ compiler supporting C++11 or higher (e.g., GCC, Clang, MSVC).
- Windows OS (Note: Uses `Windows.h` for system commands like `Sleep` and `cls`).

### Compilation
Compile the project using the following command:

```bash
g++ main.cpp -o ProjectManager
