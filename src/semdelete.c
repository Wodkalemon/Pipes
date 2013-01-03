#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "../include/sem.h"

int main(void) {	
	key_t key = ftok(".",0);

	if (sem_delete(sem_create(key)) < 0) {
		perror("sem_delete()");
	}
	return EXIT_SUCCESS;
}
