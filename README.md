Copy-on-Write Memory Demonstrator
Batch: 22
Project type: Operating Systems Mini Project
Platform: Ubuntu/Linux
Language: C  
1. Project Overview
This project demonstrates the basic idea of Copy-on-Write (COW) memory behavior associated with the Linux fork() system call. After fork(), the parent and child processes have separate logical address spaces. Linux can initially share physical memory pages and copy a page when a process writes to it.
The demonstration program creates a child process using fork(). The child changes its own variable and prints its value, while the parent prints its own value. This shows that changes made by one process do not change the other process's variable.
Important: Different printed values demonstrate process isolation, but do not by themselves prove exactly when the operating system copied a physical memory page. Direct verification of page-level COW requires additional tools or instrumentation.

2. Requirements
- Ubuntu or another Linux distribution
- GCC compiler
- Terminal access
Install the compiler tools on Ubuntu:
sudo apt update
sudo apt install build-essential
Check that GCC is installed:
gcc --version
3. Source Code
Create a file named cow_demo.c and paste the following code:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int value = 100;
    pid_t pid;

    printf("Before fork(): value = %d\n", value);
    fflush(stdout);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child process */
        value = 200;
        printf("Child process: value = %d\n", value);
    } else {
        /* Parent process */
        wait(NULL);
        printf("Parent process: value = %d\n", value);
    }

    return EXIT_SUCCESS;
}
4. Build and Run
Open a terminal and run:
mkdir -p cow_project
cd cow_project
nano cow_demo.c
Paste the source code above into Nano. Save with Ctrl+O, press Enter, then exit with Ctrl+X.
Compile:
gcc -Wall -Wextra -o cow_demo cow_demo.c
Run:
./cow_demo
5. Example Output
The output should be similar to the following (the exact order can vary unless synchronization is used):
Before fork(): value = 100
Child process: value = 200
Parent process: value = 100
The child changes its own copy of value to 200. The parent's value remains 100.
6. Test Checklist
- [ ] GCC is installed (gcc --version).
- [ ] The program compiles without errors.
- [ ] Running ./cow_demo creates parent and child output.
- [ ] The child prints 200.
- [ ] The parent prints 100.
- [ ] Capture a screenshot of the terminal output for the project report.
Record actual test results and attach screenshots before submission. Do not report tests as passed until you have run them on your system.
7. Repository Structure
A simple project folder can use this structure:
cow_project/
├── cow_demo.c
├── README.md
└── cow_demo        # generated after compilation; usually not committed
To use this file as the repository README, rename it to README.md and place it beside cow_demo.c.
8. Limitations and Future Improvements
This starter program demonstrates process isolation and the behavior commonly associated with COW. It does not measure physical page sharing or directly detect the page fault that triggers a COW copy. Possible extensions include examining /proc information, using suitable Linux memory-inspection tools, or adding a controlled memory-region experiment and documenting its measurements.
9. Team
- Navaneeth
- Chaitanya
- T. Sai Krishna
Confirm the official full names, roll numbers, and guide details with the project team before final submission.
10. License / Academic Use
Prepared as an educational Operating Systems mini project. Add your institution's required license or academic integrity statement if applicable.
