#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define ITERATIONS 20
#define PARTS 3

int pipeFd;

void sigint_handler() {
	printf("Das Programm wird beendet!\n");
	if (close(pipeFd) < 0) {
		perror("close()");
	}
	exit(EXIT_SUCCESS);
}

int main (int argc, char **argv) {
	int i, j, k, wCount, sleep1, sleep2, no;
	char *pipe;
	struct sigaction saQuit;
	char *msg = calloc (256, sizeof(char));

	if (argc != 5) {
		(void) printf("usage: %s <pipe> <no> <sleep1> <sleep2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&saQuit, 0, sizeof(saQuit));
	saQuit.sa_handler = sigint_handler;
	sigaction(SIGINT, &saQuit, NULL);
	
	pipe = argv[1];
	no = atoi(argv[2]);
	sleep1 = atoi(argv[3]);
	sleep2 = atoi(argv[4]);

	pipeFd = open(pipe, O_WRONLY);
	if (pipeFd < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	for (i=0; i<ITERATIONS; i++) {
		for (j=0; j<PARTS; j++) {
			for (k=0; k<no; k++) { 
				wCount = write (pipeFd, "\t", 1);
				if (wCount < 0) {
					perror("write()");
				}
			}
			sprintf(msg, "%d : %d : Teil%d\n", getpid(), i, j+1);
			wCount = write (pipeFd, msg, strlen(msg));
			if (wCount < 0) {
				perror("write()");
			}
			sleep(sleep2);
		}
		sleep(sleep1);
	}

	sprintf(msg, "%c", EOF);
	wCount = write (pipeFd, msg, strlen(msg));
	if (wCount < 0) {
		perror("write()");
	}

	if (close(pipeFd) < 0) {
		perror("close()");
	}

	return EXIT_SUCCESS;
}
