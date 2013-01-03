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

int main (int argc, char **argv, char **envp) {
	int rCount;
	char c;
	char *pipe;
	struct sigaction saQuit;
	
	if (argc != 2) {
		(void) printf("usage: %s <pipe>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&saQuit, 0, sizeof(saQuit));
	saQuit.sa_handler = sigint_handler;
	sigaction(SIGINT, &saQuit, NULL);

	printf("Das Programm kann mit [ctrl]+[c] beendet werden\n");

	pipe = argv[1];

	if (strcmp(pipe, "anonym") == 0) {
		pipeFd = atoi(envp[0]);
	} else {
		pipeFd = open(pipe, O_RDONLY);
	}

	if (pipeFd < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	
	do {
		rCount = read (pipeFd, &c, 1);
		if (rCount < 0) {
			perror("read()");
		}
		printf("%c", c);
	} while(c != EOF);

	if (close(pipeFd) < 0) {
		perror("close()");
	}
	

	return EXIT_SUCCESS;
}
