#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // 1. Ensure the user provided exactly two arguments (PID and Signal Number)
    if (argc != 3) {
        printf("Usage: %s <PID> <SIGNAL_NUMBER>\n", argv[0]);
        printf("Example: %s 1234 2   (Sends SIGINT/Ctrl+C to PID 1234)\n", argv[0]);
        return 1;
    }

    // 2. Convert command-line string arguments into integers
    pid_t target_pid = atoi(argv[1]);
    int sig_num = atoi(argv[2]);

    printf("Sending signal %d to process %d...\n", sig_num, target_pid);

    // 3. Use the kill() system call to fire the signal
    if (kill(target_pid, sig_num) == 0) {
        printf("🟢 Success! Signal delivered.\n");
    } else {
        // If it fails (e.g., process doesn't exist, or you don't have permission)
        perror("❌ Error sending signal");
        return 1;
    }

    return 0;
}

