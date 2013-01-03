#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "../include/sem.h"


int main(void) {
	
	key_t key;
	int semid;

	key = ftok(".",0);
	semid	= sem_create(key);
	if (semid < 0) {
		perror("sem_create()");
		exit(EXIT_FAILURE);
	}
	(void) printf("Semaphore mit ID %d erstellt\n", semid);

	V(semid);
	return EXIT_SUCCESS;
}

