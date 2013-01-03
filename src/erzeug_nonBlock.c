#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int pipeFd;

void sigint_handler() {
	printf("Das Programm wird beendet!\n");
	if (close(pipeFd) < 0) {
		perror("close()");
	}
	exit(EXIT_SUCCESS);
}

int main (int argc, char **argv) {
	char *pipe;
	struct sigaction saQuit;
	int wCount, i;
	char *msg = calloc (256, sizeof(char));

	if (argc != 2) {
		(void) printf("usage: %s <pipe>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&saQuit, 0, sizeof(saQuit));
	saQuit.sa_handler = sigint_handler;
	sigaction(SIGINT, &saQuit, NULL);
	
	pipe = argv[1];
	pipeFd = open(pipe, O_RDWR | O_NONBLOCK);
	
	if (pipeFd < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	for(i=0;;i++) {
		wCount = write (pipeFd, "1", 1);
		if (wCount < 0) {
			break;
			perror("write()");
		}
	}

	(void) printf("%d kB\n", i);

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
