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

int check_row(int nums[N][N], int row) {
	// Determine which requirments (1-9) are present.
	int reqs[N];
	int num;
	for (int i=0; i<N; i++) {
		reqs[i] = 0;
		num = nums[row][i];
		reqs[num-1] = 1;
	}
	// Return 0 if a requirment is not present in row.
	for (int i=0; i<N; i++) {
		if (reqs[i] == 0)
			return 0;
	}
	// Return 1 if digits 1-9 are present in row.
	return 1;
}

int check_col(int nums[N][N], int col) {	
	// Determine which requirments (1-9) are present.
	int reqs[N];
	int num;
	for (int i=0; i<N; i++) {
		reqs[i] = 0;
		num = nums[i][col];
		reqs[num-1] = 1;
	}
	// Return 0 if a requirment is not present in col.
	for (int i=0; i<N; i++) {
		if (reqs[i] == 0)
			return 0;
	}
	// Return 1 if digits 1-9 are present in col.
	return 1;
}

void luke() {
	int nums[N][N];
	get_input(nums);
}

int main (int argc, char** argv) {
	//initialize 9x9 array of integers
	Nnt nums [9][N];
	//initialize array using getInput method
	getInput(nums);

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

	return 0;
}


int method() {

}
