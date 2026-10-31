#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("[HELLO PROGRAM] Hello from the newly executed program!\n");
    printf("[HELLO PROGRAM] My PID is %d. Notice it is the exact same as the child!\n", getpid());
    printf("[HELLO] My argv[0] is %s\n", argv[0]);
    return 0;
}

