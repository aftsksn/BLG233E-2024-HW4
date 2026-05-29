# Process Scheduler using Min-Heap (CFS Simulator)

A command-line Process Scheduler implemented in C, inspired by the Linux kernel's Completely Fair Scheduler (CFS)[cite: 14]. This project utilizes a custom-built, generic Min-Heap data structure to efficiently manage and schedule simulated processes based on their virtual runtimes[cite: 12, 14].

## 🚀 Features

*   **Completely Fair Scheduler (CFS) Logic:** Ensures fair CPU time distribution by tracking each process's `vruntime` (virtual runtime). The scheduler always picks the process with the lowest `vruntime` to execute next[cite: 13, 14].
*   **Generic Min-Heap Implementation:** Features a dynamically resizing min-heap capable of storing any data type using `void*` pointers. It guarantees O(log n) time complexity for insertions and extractions[cite: 12].
*   **Dynamic Priority Management:** Processes support "nice" values ranging from -20 (highest priority) to +19 (lowest priority). A process's nice value dynamically affects how quickly its virtual runtime increases during execution[cite: 13, 17].
*   **Zero Memory Leaks:** Thoroughly profiled using Valgrind. All dynamically allocated resources (heap arrays, process queues, node swapping buffers) are strictly managed and safely deallocated[cite: 16, 18, 19].
*   **Test-Driven Development:** Built with a testing infrastructure utilizing the `munit` framework[cite: 11].

## 🛠️ Technology Stack

*   **Language:** C
*   **Build System:** Make / GCC[cite: 11]
*   **Testing:** `munit`[cite: 11]
*   **Memory Profiling:** Valgrind[cite: 11]

## 📂 Project Structure

*   `src/min_heap.c` & `include/min_heap.h`: The core generic min-heap implementation, handling memory reallocation (`heapify_up`, `heapify_down`, `swap`)[cite: 12, 16].
*   `src/process.c` & `include/process.h`: Process structure definition, creation, and `vruntime` calculation logic based on nice values[cite: 13, 17].
*   `src/scheduler.c` & `include/scheduler.h`: The CFS orchestrator that manages the process queue and handles the time slice ticks[cite: 14, 18].
*   `src/main.c`: A simulation runner that demonstrates the scheduler handling multiple processes with varying priorities over a set of CPU ticks[cite: 15].

## ⚙️ Getting Started

### Prerequisites
Ensure you have `gcc` and `make` installed on your system. For memory testing, `valgrind` is required.

### Compilation & Execution

1.  **Clone the repository:**
```bash
    git clone https://github.com/aftsksn/BLG233E-2024-HW4.git
    cd BLG233E-2024-HW4
    ```

2.  **Build the project:**
```bash
    make build
    ```
    This compiles the source files and places the executable in the `bin/` directory[cite: 11].

3.  **Run the scheduler simulation:**
```bash
    make run
    ```

### Testing & Debugging

*   **Run Unit Tests:** 
```bash
    make tests
    ```
    This will clean previous builds, compile the test binaries using the `munit` library, and run the test suite[cite: 11].

*   **Run Memory Profiler:**
```bash
    make valgrind
    ```
    This executes the program through Valgrind to ensure there are zero memory leaks[cite: 11, 19].