# Multi-Process-and-Threading-Assignments

C programming assignments on process management and multithreading. Includes a multi-process file-handling program and a restaurant ordering system using semaphores and threads.

## Overview

This repository contains two C programming assignments demonstrating process management and multithreading concepts:

1. **Multi-Process File Handling** – Uses forked child processes to compute factorials, list running processes, and calculate averages while handling file I/O.
2. **Multi-Threaded Restaurant Ordering System** – Simulates a restaurant workflow with customers, chefs, and waiters using threads and semaphores.

---

## Assignment 1: Multi-Process File Handling

### Description

This program reads input data from a file and processes it using three child processes:

- **Factorial Calculation** – Computes the factorial of a given number.
- **Process Listing** – Retrieves and saves a list of running processes.
- **Average Calculation** – Computes the average of a set of numbers.

The parent process manages execution and consolidates outputs.

### Compilation & Execution

```sh
gcc -o assignmentB assignmentB.c
./assignmentB
```

### Expected Output

- `factorial_result.txt` (Factorial computation result)
- `process_list.txt` (List of running processes)
- `average_result.txt` (Computed average of numbers)

---

## Assignment 2: Multi-Threaded Restaurant Ordering System

### Description

This program simulates a restaurant where:
    - **Customers** place orders.
    - **Chefs** prepare food.
    - **Waiters** serve the orders.

Synchronization is managed using counting semaphores to ensure smooth order handling.

### Compilation & Execution

```sh
gcc -o restaurant_system 12thassignmentB.c -pthread
./restaurant_system
```

### Features

- Uses semaphores to limit the number of simultaneous customers, active orders, and serving operations.
- Proper synchronization to prevent race conditions.

---

## License

This project is for educational purposes. Feel free to modify and enhance it!
