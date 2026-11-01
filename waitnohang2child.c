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
        printf("[CHILD] Ana PID %d is going to play outside for 4 seconds...\n", getpid());
        sleep(4);
        printf("[CHILD] Ana is done! Exiting now.\n");
        exit(0); 
    } else {
        // --- PARENT PROCESS ---

	pid_t child_pid2 = fork();

	if (child_pid2 == 0) {
		// --- CHILD PROCESS ---
		printf("[CHILD] Elsa PID %d is going to play outside for 4 seconds...\n", getpid());
		sleep(6);
		printf("[CHILD] Elsa is done! Exiting now.\n");
		exit(0); 
	} else {
		//
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
		    else if (result > 0) {
			// Result matches Child PID means: "The child just finished!"
			printf("\n🎉 [PARENT] Ah, %d child has finished! Cleaning complete.\n", result);
			//break; //No break if more than one child, need to wait for others 
		    } 
		    else {
			// If something went wrong (like no child exists)
			printf("[PARENT] All children done playing\n");
			break;
		    }

		}
	}
    }
    return 0;
}

