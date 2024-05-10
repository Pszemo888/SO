#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <syslog.h>

volatile int handled_signals = 0;
volatile bool flag = true;

void handler(int signum) {
    syslog(LOG_INFO, "Otrzymano sygnał %d\n", signum);
    handled_signals++;

    if (handled_signals >= 3) {
        flag = false;
    }
}

int main(void) {
    openlog("mój_program", LOG_PID, LOG_USER); 
    signal(SIGQUIT, handler);

    while(flag) {
        syslog(LOG_INFO, "Pracuję...\n");
        sleep(1);
    }

    syslog(LOG_INFO, "Zamykanie programu...\n");
    closelog(); 
    return 0;
}

