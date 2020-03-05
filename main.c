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

void one_thread (int nums [N][N]) {
	
	
}

void multi_thread (int nums [N][N]) {	
	//declare N threads
	pthread_t tid[11];

	for (int i = 0; i < 11; i++) {
		if (i == 0) {
			//create thread for checking column
			pthread_create(&tid[i], 0, getCol, NULL);
		}
		else if (i == 1) {
			//create thread for checking rows
			pthread_create(&tid[i], 0, getRow, NULL);
		}
		else {
			//create threads for checking boxes
			pthread_create(&tid[i], 0, getBox, NULL);
		}
	}

	for (int i = 0; i < 11; i++) {
		//join all 11 threads
		pthread_join(tid[i], NULL);
	}
}

int main (int argc, char** argv) {
	//initialize 9x9 array of integers
	int nums [N][N];
	//initialize array using getInput method
	getInput(nums);

	//print out the sudoku board from the array
	print_board(nums);

	// if user enters 1, single-thread it
	if (atoi(argv[1]) == 1) {
		one_thread(int nums [N][N]);
	}
	// if user enters 2, multi-thread it
	else if (atoi(argv[1]) == 2) {
		multi_thread(int nums [N][N]);
	}

	return 0;
}
