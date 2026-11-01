#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("[PARENT] Forking a child...\n");
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // --- CHILD PROCESS ---
        printf("[CHILD] I'm going to play outside for 4 seconds...\n");
        sleep(4);
        printf("[CHILD] I'm done! Exiting now.\n");
        exit(0); 
    } else {
        // --- PARENT PROCESS ---
        int status;
        pid_t result;


	/*
	printf("[PARENT], waiting for child\n");
	waitpid(-1, &status, 0);
	printf("[PARENT], child exited\n");
	exit(0);
	*/

        printf("[PARENT] I will clean the house while checking on the child.\n\n");

        // Keep looping until waitpid actively catches the exited child
        while (1) {
            // Check status. -1 means any child, WNOHANG means do not block!
            result = waitpid(-1, &status, WNOHANG);

            if (result == 0) {
                // Result 0 means: "The child is still alive and running!"
                printf("[PARENT] Checked on child: Still playing. I'll sweep for 1 second...\n");
                sleep(1); // Do some "work"
            } 
            else if (result == child_pid) {
                // Result matches Child PID means: "The child just finished!"
                printf("\n🎉 [PARENT] Ah, child has finished! Cleaning complete.\n");
                break;
            } 
            else {
                // If something went wrong (like no child exists)
                perror("[PARENT] Error in waitpid");
                break;
            }

        }
    }
    return 0;
}

