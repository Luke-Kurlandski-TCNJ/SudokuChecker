#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define N 9

void get_input(int nums[N][N]) {
	// Open the file.
	FILE *f = fopen("input.txt", "r");
	if (f==NULL) 
		printf("Error Opening input.txt\n");
	// Read file and fill nums.
	for (int j=0; j<N; j++) {
		for (int i=0; i<N; i++) {
			fscanf(f, "%1d", &nums[i][j]);
		}
	}
	// Close the file.
	fclose(f);
}

void print_board(int nums[N][N]) {
	printf("Input Board:\n");
	for (int j=0; j<N; j++) {
		for (int i=0; i<N; i++) {
			printf("%d ", nums[i][j]);
		}
		printf("\n");
	}		
}

void luke() {
	int nums[N][N];
	get_input(nums);
}

int main (int argc, char** argv) {
	int** arr = getInput(); //initialize array using getInput method

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
