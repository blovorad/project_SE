#include "ipcTools.h"

int semalloc(key_t key, int valInit) {
	int semid;

	//Création
	if ((semid=semget(key, 1, IPC_CREAT|IPC_EXCL|0644))==-1) {
		if ((semid=semget(key, 1, 0))==-1) {
			perror("Impossible to create semaphore\n");
			return -1;
		}
	}
	
	//Initialisation
	if (semctl(semid, 0, SETVAL, valInit)==-1) {
		perror("Impossible to initialize semaphore\n");
		semctl(semid, 0, IPC_RMID, 0);
		return -1;
	}

	
	return semid;
}

void P(int semid) {
	struct sembuf sopsP[1] = {0, -1, 0};
	//sops[0].sem_num=0;
	//sops[0].sem_op=-1;
	//sops[0].sem_flg=0;
	
	semop(semid, sopsP, 1);
}

void V(int semid) {
	struct sembuf sopsV[1] = {0, +1, 0};
	//sops[0].sem_num=0;
	//sops[0].sem_op=1;
	//sops[0].sem_flg=0;
	
	semop(semid, sopsV, 1);
}

int semfree(int semid) {
	
	if (semctl(semid, 0, IPC_RMID, 0)==-1) {
		perror("Impossible to destroy semaphore\n");
		return -1;
	}

	return 0;
}
