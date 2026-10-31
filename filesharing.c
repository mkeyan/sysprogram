#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    // Open a file BEFORE forking so the file description is shared
    int fd = open("alphabet.txt", O_RDONLY);
    char buffer[5] = {0,0,0,0,0};
    int fd2;
    close(2);//closing stderr
    fd2 = open("a.out", O_RDONLY);

    printf("fd before forking is %d, %d\n", fd, fd2);
    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD PROCESS ---
	printf("[CHILD] fd is %d\n", fd);
        read(fd, buffer, 4); // Reads 'ABCD'
        printf("[CHILD] I read the first 4 bytes: %s\n", buffer);
	printf("[CHILD] closed fd\n");
	close(fd);
    } else {
        // --- PARENT PROCESS ---
	printf("[PARENT] fd is %d\n", fd);
        wait(NULL); // Wait for child to read first
        read(fd, buffer, 4); // Reads the NEXT 4 bytes because the cursor moved!
        printf("[PARENT] I read the next 4 bytes: %s\n", buffer);
        printf("[PARENT] This proves we share the same file cursor position!\n");
        printf("[PARENT] This also proves closing file in child does not affect the fd in the parent\n");
        close(fd);
    }
    return 0;
}

