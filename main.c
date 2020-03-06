#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define N 9

int nums[N][N];
int solution = 1;
int deltaT = 0;

typedef struct {
	int row;
	int col;
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
	printf("BOARD STATE IN (input.txt)\n");
	for (int j=0; j<N; j++) {
		for (int i=0; i<N; i++) {
			printf("%d ", nums[i][j]);
		}
		printf("\n");
	}
	printf("SOLUTION: ");
	if (solution == 1)
		printf("YES ");
	else
		printf("NO ");
	printf("(time %d )", deltaT);
}

void* check_row(void* param) {
	params* data = param;
	int reqs[N];
	int n;
	// Determine which requirments (1-9) are present.
	for (int col=0; col<N; col++) {
		reqs[col] = 0;
		n = nums[data->row][col];
		reqs[n-1] = 1;
	}
	// Return 0 if a requirment is not present in row.
	for (int i=0; i<N; i++) {
		if (reqs[i] == 0) {
			solution = 0;
			return 0; //return because solution is already incorrect
		}
	}
}

void* check_rows(void* param) {
	// Create one thread for each row.
	pthread_t tid[N];
	for (int i=0; i<N; i++) 
		pthread_create(&tid[i], 0, check_row, NULL);
	for (int i=0; i<N; i++) 
		pthread_join(tid[i], NULL);
}

void* check_col(void* param) {
	params* data = param;
	int reqs[N];
	int n;
	// Determine which requirments (1-9) are present.
	for (int row=0; row<N; row++) {
		reqs[row] = 0;
		n = nums[row][data->col];
		reqs[n-1] = 1;
	}
	// Return 0 if a requirment is not present in row.
	for (int i=0; i<N; i++) {
		if (reqs[i] == 0) {
			solution - 0;
			return 0; //return because solution is already incorrect
		}
	}
}

void* check_cols(void* param) {
	// Create one thread for each row.
	pthread_t tid[N];
	for (int i=0; i<N; i++) 
		pthread_create(&tid[i], 0, check_col, NULL);
	for (int i=0; i<N; i++) 
		pthread_join(tid[i], NULL);
}

void* check_box(void* param) {

}

void* check_boxes(void* param) {

}

void one_thread () {
	// Store information of cuurent coordinates.
	params *data = (params*)malloc(sizeof(params));
	// Check all rows.
	for (int row=0; row<N; row++) {	
		data->row = row;
		check_row(data);
	}
	// Check all columns.
	for (int col=0; col<N; col++) {	
		data->col = col;
		check_col(data);
	}
	// Check all boxes.
	for (int row=0; row<N; row+=3) {
		for (int col=0; col<N; col+=3) {
			data->row = row;
			data->col = col;
			check_box(data);
		}
	}
		
}

void multi_thread () {	
	//declare N threads
	pthread_t tid[3];
	//create threads for checking cols
	pthread_create(&tid[0], 0, check_cols, NULL);
	//create threads for checking rows
	pthread_create(&tid[1], 0, check_rows, NULL);
	// Check Boxes 
	pthread_create(&tid[2], 0, check_boxes, NULL);

	//join all 3 threads.
	for (int i = 0; i < 3; i++) 
		pthread_join(tid[i], NULL);
}

int main (int argc, char** argv) {
	//initialize array using getInput method
	get_input(nums);

	// if user enters 1, single-thread it
	if (atoi(argv[1]) == 1) {
		one_thread(nums);
	}
	// if user enters 2, multi-thread it
	else if (atoi(argv[1]) == 2) {
		multi_thread(nums);
	}

	//print out the sudoku board from the array
	print_board(nums);
	
	return 0;
}
