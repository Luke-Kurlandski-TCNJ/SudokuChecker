#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>



int main (int argc, char** argv) {
	int nums [9][9]; //create array of integers
	getInput(nums); //initialize array using getInput method

	pthread_t tid[11]; //declare N threads

	for (int i = 0; i < 11; i++) {
		if (i == 0) {
			pthread_create(&tid[i], 0, getCol, NULL); //create threads for checking columns
		}
		else if (i == 1) {
			pthread_create(&tid[i], 0, getRow, NULL); //create thread for checking rows
		}
		else {
			pthread_create(&tid[i], 0, getBox, NULL); //create threads for checking boxes
		}
	}

	for (int i = 0; i < 11; i++) {
		pthread_join(tid[i], NULL); //join all 11 threads
	}

	return 0;
}

int method() {

}
