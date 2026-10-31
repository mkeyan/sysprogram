#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int secret_number = 42; // Shared initially, but copied on change

    printf("Before fork, secret_number = %d\n\n", secret_number);

    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD PROCESS ---
	int ecode = 0;
        printf("[CHILD] secret_number when staring is %d\n", secret_number);
        printf("[CHILD] Changing secret_number to 99...\n");
        secret_number = 99;
        printf("[CHILD] My secret_number is now: %d\n", secret_number);

	/*
	 * Usage: clone [<exit_code> [<anything>]]
	 * if there is anything in the second argument that means use exit system call instead 
	 * of returning from the program
	 */
	if (argc > 1) {   
            ecode = atoi(argv[1]);
	}
	if (argc > 2) {
	   exit(ecode);
	   //does not reach
	}
	return ecode;
    } else {
        // --- PARENT PROCESS ---
	int wstatus;
        printf("\n[PARENT] I am going to wait for my child pid %d to exit \n", pid);
        wait(&wstatus); // Wait for child to finish changing its variable
        printf("\n[PARENT] Child exited with status 0x%x, %d\n", wstatus, WEXITSTATUS(wstatus));
        printf("\n[PARENT] Child is done. My secret_number is STILL: %d\n", secret_number);
        printf("[PARENT] This proves memory is a separate copy!\n");
    }
    return 0;
}

