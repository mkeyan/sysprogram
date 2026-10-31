#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 1. CHANGE THIS NUMBER TO EXPERIMENT:
// 2 = SIGINT  (Ctrl+C)
// 10 = SIGUSR1 (Custom User Signal 1)
// 12 = SIGUSR2 (Custom User Signal 2)
#define TARGET_SIGNAL 1

// The custom function that runs when the signal hits
void custom_handler(int signum) {
    printf("\n📬 [HANDLER] Success! Caught signal number %d!\n", signum);
    printf("[HANDLER] The sender program reached out and touched our memory!\n");
}

int main() {
    // 2. Print our PID so we know who to target from the sender
    printf("🎯 Target Receiver Program Started.\n");
    printf("===================================\n");
    printf("My Process ID (PID) is: %d\n", getpid());
    printf("I am listening for signal number: %d\n", TARGET_SIGNAL);
    printf("===================================\n\n");

    // 3. Register our custom print function for our chosen signal
    signal(TARGET_SIGNAL, custom_handler);
    signal(2, custom_handler);
    signal(9, custom_handler);
    kill(getpid(), 1);

    printf("Waiting patiently... Send me a signal from another terminal!\n");
    
    // An infinite loop to keep the program alive while we wait
    while(1) {
        printf("... still waiting ...\n");
        sleep(3); 
    }

    return 0;
}

