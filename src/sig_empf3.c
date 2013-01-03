#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define ALARM_PERIOD 1
#define MAX_COUNT 1000000000

volatile int count = 0;
struct sigaction saUsr1;
struct sigaction saUsr2;
struct sigaction saTerm;
struct sigaction saAlarm;
struct sigaction saNix;

void sigusr1_handler () {
    sigaction(SIGUSR2, &saNix, &saUsr2);
    sigaction(SIGALRM, &saNix, &saAlarm);
	(void) printf("Signal SIGUSR1 empfangen. Start Zählen\n");
	for(count=0; count<MAX_COUNT; count++);
	(void) printf("Bis MAX_COUNT gezählt\n");
    sigaction(SIGUSR2, &saUsr2, NULL);
    sigaction(SIGALRM, &saAlarm, NULL);
	alarm(ALARM_PERIOD);
}

void sig_nix() {
}

void sigusr2_handler () {
	(void) printf("Signal SIGUSR2 empfangen\n");
}

void sigterm_handler () {
	(void) printf("Programmende\n");
	exit(EXIT_SUCCESS);
}

void sigalarm_handler () {
	(void) printf("Timer abgelaufen, count: %d\n", count);
	alarm(ALARM_PERIOD);
}

int main (int argc, char **argv) {
	
	if(argc > 1) {
		(void) printf("%s braucht keine Argumente\n", argv[0]);
	}	

	(void) printf("PID %d\n", getpid());
	
    memset(&saNix, 0, sizeof(saNix));
    saNix.sa_handler = sig_nix;

    memset(&saUsr1, 0, sizeof(saUsr1));
    saUsr1.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &saUsr1, NULL);

    memset(&saUsr2, 0, sizeof(saUsr2));
    saUsr2.sa_handler = sigusr2_handler;
    sigaction(SIGUSR2, &saUsr2, NULL);

    memset(&saTerm, 0, sizeof(saTerm));
    saTerm.sa_handler = sigterm_handler;
    sigaction(SIGTERM, &saTerm, NULL);

    memset(&saAlarm, 0, sizeof(saAlarm));
    saAlarm.sa_handler = sigalarm_handler;
    sigaction(SIGALRM, &saAlarm, NULL);

	alarm(ALARM_PERIOD);
	
	for(;;) {
		pause();
	}

	return EXIT_SUCCESS;
}

