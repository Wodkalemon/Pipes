#ifndef __SEM_H__
#define __SEM_H__

/** 
  * Beschreibung:	Erstellt ein Semaphore mit der Semaphorenmenge 0 für den einen bestimmten key, wenn zum angegebenen Key bereits ein Semaphore existiert, wird dieser zurückgegeben.
  * Im Falle eines Fehlers wird errno gesetzt
  * RETURN:			ID des Semaphores, der zum übergebenen Key gehört, oder -1 im Fehlerfall. 
  */
int sem_create (key_t key);

/**
  * Beschreibung:	Gibt zu einem Key den zugehörigen Semaphore zurück. Wenn es zu diesem Key kein Semaphore gibt, gibt open mit -1 zurück und errno wird gesetzt.
  * RETURN:			ID des Semaphores, der zu key gehört, falls dieser bereits existiert, sonst -1
  */
int sem_open (key_t key);

/**
  * Beschreibung:	Löscht den Semaphore mit der ID semid. Vorrauasetzung ist, dass der ausführende Benuter die Berechtigung dazu hat.
  * Im fehlerfall wird -1 zurückgegeben und errno ist gesetzt. Bei Erfolg 0
  * RETURN: 		0 oder -1 im Fehlerfall;
  */
int sem_delete (int semid);

/**
  *	Beschreibung:	Erhöht den Wert des Semaphores mit der ID semid um 1
  * RETURN:			0 oder -1 im Fehlerfall, ernno wird gesetzt
  */
int V (int semid);

/**
  *	Beschreibung:	Verringert den Wert des Semaphores mit der ID semid um 1
  * RETURN:			0 oder -1 im Fehlerfall, ernno wird gesetzt
  */
int P (int semid);

/**
  * Beschreibung:	Gibt die aktuellen Wert des Semaphores mit der ID semid zurück und im Fehlerfall -1 errno wird gesetzt
  */
int sem_read (int semid);

#endif /*!__SEM_H__*/
