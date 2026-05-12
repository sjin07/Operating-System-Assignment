#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// A simple CPU-bound dummy task to consume time slice
void spin() {
    volatile int x = 0;
    for (int i = 0; i < 20000; i++) {
        for (int j = 0; j < 10000; j++) {
            x = x + 1;
        }
    }
}

int main(int argc, char *argv[])
{
    printf("=== TEST START ===\n");

    int pid = fork();

    if (pid < 0) {
        printf("fork failed!\n");
        exit(1);
    }

    if (pid == 0) {
        // --- CHILD PROCESS ---
        // Set child's nice value to 10
        setnice(getpid(), 10);
        
        // Spin to consume CPU time
        spin();
        
        exit(0);
    } else {
        // --- PARENT PROCESS ---
        // Set parent's nice value to 0
        setnice(getpid(), 0);

        // Spin to consume CPU time 
        // (Slightly shorter so parent finishes its loop while child is still running)
        volatile int x = 0;
        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 10000; j++) {
                x = x + 1;
            }
        }

        // Call the modified ps() system call to print all processes
        ps(0);

        // Wait for the child to finish
        wait(0);
    }

    exit(0);
}