#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define N 9

int nums[N][N];

typedef struct {
	int row;
	int column;
} params;

void get_input() {
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

void print_board() {
	printf("Input Board:\n");
	for (int j=0; j<N; j++) {
		for (int i=0; i<N; i++) {
			printf("%d ", nums[i][j]);
		}
		printf("\n");
	}		
}

void* check_rows(void* param) {
	int reqs[N];
	int n;
	// Loop through every row.
	for (int row=0; row<N; row++) {
	// Determine which requirments (1-9) are present.
		for (int col=0; col<N; col++) {
			reqs[col] = 0;
			n = nums[row][col];
			reqs[n-1] = 1;
		}
		// Return 0 if a requirment is not present in row.
		for (int i=0; i<N; i++) {
			if (reqs[i] == 0)
				return (void*) 0;
		}
	}
	// Return 1 if digits 1-9 are present in row.
	return (void*) 1;
}

void* check_cols(void* param) {	
	int reqs[N];
	int n;
	// Loop through every row.
	for (int col=0; col<N; col++) {
	// Determine which requirments (1-9) are present.
		for (int row=0; row<N; row++) {
			reqs[row] = 0;
			n = nums[row][col];
			reqs[n-1] = 1;
		}
		// Return 0 if a requirment is not present in row.
		for (int i=0; i<N; i++) {
			if (reqs[i] == 0)
				return (void*) 0;
		}
	}
	// Return 1 if digits 1-9 are present in row.
	return (void*) 1;
}

void* check_box(void* param) {

}

void one_thread () {
		
}

void multi_thread () {	
	//declare N threads
	pthread_t tid[11];
	//create threads for checking cols
	pthread_create(&tid[0], 0, check_cols, NULL);
	//create threads for checking rows
	pthread_create(&tid[1], 0, check_rows, NULL);

	//create threads for checking boxes
	for (int i = 2; i < 11; i++) {
		pthread_create(&tid[i], 0, check_box, NULL);
	}

	for (int i = 0; i < 11; i++) {
		//join all 11 threads
		pthread_join(tid[i], NULL);
	}
}

int main (int argc, char** argv) {
	//initialize array using getInput method
	get_input(nums);

	//print out the sudoku board from the array
	print_board(nums);

	// if user enters 1, single-thread it
	if (atoi(argv[1]) == 1) {
		one_thread(nums);
	}
	// if user enters 2, multi-thread it
	else if (atoi(argv[1]) == 2) {
		multi_thread(nums);
	}

	return 0;
}
