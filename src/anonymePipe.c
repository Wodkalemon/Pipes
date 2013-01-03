#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include "../include/sem.h"

int semid;
int pipefd[2];

int main (void) {
	pid_t pid1, pid2;
	key_t key;
	int status;
	char *argv[6];
	char *envp[2];
	char fd[16];

	if (pipe(pipefd) < 0) {
		perror("pipe()");
		exit(EXIT_FAILURE);
	}

	/* Semaphor erzeugen */
	key = ftok(".",0);
	semid	= sem_create(key);
	if (semid < 0) {
		perror("sem_create()");
		if (sem_delete(semid) < 0) {
			perror("sem_delete()");		
		}	
		exit(EXIT_FAILURE);
	}
	V(semid);
	/* Kinder erzeugen */
	pid1 = fork();
	if (pid1 < 0) {
		perror("fork()");
		if (sem_delete(semid) < 0) {
			perror("sem_delete()");		
		}	
		exit(EXIT_FAILURE);
	}

	if (pid1 != 0) {
		pid2 = fork();
		if (pid2 < 0) {
			perror("fork()");
			if (sem_delete(semid) < 0) {
				perror("sem_delete()");		
			}	
			exit(EXIT_FAILURE);
		}
	}
	
	if (pid1 == 0) {
		if (close(pipefd[0]) < 0) {
			perror("close()");
		}
		sprintf(fd,"%d",pipefd[1]);
		argv[0] = "erzeug";
		argv[1] = "anonym";
		argv[2] = "1";
		argv[3] = "2";
		argv[4] = "4";
		argv[5] = NULL;
		envp[0] = fd;
		envp[1] = NULL;

		printf("%s PID %d\n", argv[0], getpid());
	
		execve("erzeug", argv, envp);
	} 
	
	if (pid2 == 0 && pid1 != 0) {
		if (close(pipefd[1]) < 0) {
			perror("close()");
		}
		sprintf(fd,"%d",pipefd[0]);
		argv[0] = "verbr";
		argv[1] = "anonym";
		argv[2] = NULL;
		envp[0] = fd;
		envp[1] = NULL;

		printf("%s PID %d\n", argv[0], getpid());

		execve("verbr", argv, envp);
	}

	if (wait(&status) < 0) {
		perror("wait()");
	}
	if (wait(&status) < 0) {
		perror("wait()");
	}

	return EXIT_SUCCESS;
}
