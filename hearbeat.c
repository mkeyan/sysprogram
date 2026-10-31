#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

// This function runs every time the timer clicks down to zero
void alarm_handler(int signum) {
    static int count = 0;
    count++;
    printf("\n⏰ [HANDLER] Heartbeat #%d! SIGALRM fired by setitimer.\n", count);
}

int main() {
    // 1. Hook up our custom print handler to the SIGALRM signal
    signal(SIGALRM, alarm_handler);

    // 2. Create the master timer structure configuration
    struct itimerval timer;

    // --- THE COOLDOWN / INTERVAL ---
    // This tells the kernel what to reset the clock to AFTER it fires the first time.
    // We set it to 2 seconds and 0 microseconds.
    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;

    // --- THE FIRST START TIME ---
    // This tells the kernel how long to wait before firing the very FIRST alarm.
    // We set it to wait 5 seconds before starting the heartbeat chain.
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;

    printf("Starting the repeating timer! It will fire every 2 seconds...\n");
    printf("Press Ctrl+C when you want to stop the lesson.\n\n");

    // 3. Turn on the timer inside the kernel
    // ITIMER_REAL means track real-world clock time (like a real stopwatch)
    setitimer(ITIMER_REAL, &timer, NULL);

    // Infinite loop to sit back and watch the kernel fire the timer
    while(1) {
        printf("Main program running smoothly in the background...\n");
        sleep(5); 
    }

    return 0;
}

