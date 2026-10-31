#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char pathname[4096];
    printf("[PARENT] Starting launcher. My PID is %d\n", getpid());

    printf("\nRajiSHell>");
    scanf("%s", pathname);
   
    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD PROCESS ---
        printf("[CHILD] I am born! My PID is %d\n", getpid());
        printf("[CHILD] Wiping my memory now and transforming into './hello'...\n\n");

        // execl takes: (path_to_program, argument_0_which_is_the_name, NULL)
	if (argc > 1) {
	   execl(argv[1], argv[1], NULL);
	} else {
	   execlp(pathname, pathname, NULL);
           //execl("./hello", "./hello", NULL);
	}

        // --- IMPORTANT LESSON ---
        // If execl is successful, the lines below CANNOT run because 
        // this child's code no longer exists in memory!
        printf("[CHILD] If you see this message, execl failed to load the program!\n");
    } else {
        // --- PARENT PROCESS ---
        wait(NULL); // Wait for the morphed child to finish
        printf("\n[PARENT] My child has finished executing. Exiting launcher now.\n");
	printf("\nRajiShell>");
    }

    return 0;
}

