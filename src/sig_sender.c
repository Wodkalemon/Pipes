#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main (void) {
	int sel_op, sig1, sig2, pid, delay;
	char *killCom = calloc(256, sizeof(char));
	
	do {
		(void) printf("\n ------- Menue --------\n");
		(void) printf("[1] Ein signal schicken\n");	
		(void) printf("[2] Zwei signale schicken\n");	
		(void) printf("[3] Programm beenden\n");	

		scanf("%d", &sel_op);
		
		switch(sel_op) {
			case 1:
				(void) printf("Eingabe: <SIGNAL> <PID>\n");
				scanf("%d %d", &sig1, &pid);
				sprintf(killCom, "kill -%d %d", sig1, pid);
				system(killCom);
				break;
			case 2:
				(void) printf("Eingabe: <SIGNAL1> <SIGNAL2> <DELAY> <PID>\n");
				scanf("%d %d %d %d", &sig1, &sig2, &delay, &pid);
				sprintf(killCom, "kill -%d %d", sig1, pid);
				system(killCom);
				sleep(delay);
				sprintf(killCom, "kill -%d %d", sig2, pid);
				system(killCom);
				break;
			default:
				break;
		}

	} while (sel_op != 3);

	free(killCom);
	return EXIT_SUCCESS;
}
