#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

// Size of the soduko puzzle.
#define N 9

// Array with sudoku values.
int nums[N][N];
// Assume puzzle is a solution by default.
int solution = 1;

// Pass information via threads.
typedef struct {
	int row;
	int col;
} params;

// Pull input from txt file into 2-D array.
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

// Print the board, solution status, and time to solve.
void print_board(double deltaT) {
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
	printf("(time %lf)\n", deltaT);
}

// Check if digits 1-9 are present in single row.
void* check_row(void* param) {
	params* data = (params*)param;
	int reqs[N] = {0,0,0,0,0,0,0,0,0};
	int n;
	// Determine which requirments (1-9) are present.
	for (int col=0; col<N; col++) {
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

// Check if digits 1-9 are present in ALL rows.
void* check_rows(void* param) {
	// Create one thread for each row.
	pthread_t tid[N];
	// Store information of curent coordinates.
	params *data = (params*)malloc(sizeof(params));
	for (int i=0; i<N; i++) {
		data->row = i;
		pthread_create(&tid[i], 0, check_row, data);
	}
	for (int i=0; i<N; i++) 
		pthread_join(tid[i], NULL);
}

// Check if digits 1-9 are present in single column.
void* check_col(void* param) {
	params* data = param;
	int reqs[N] = {0,0,0,0,0,0,0,0,0};
	int n;
	// Determine which requirments (1-9) are present.
	for (int row=0; row<N; row++) {
		n = nums[row][data->col];
		reqs[n-1] = 1;
	}
	// Return 0 if a requirment is not present in row.
	for (int i=0; i<N; i++) {
		if (reqs[i] == 0) {
			printf("%d is not in column %d", i, data->col);
			solution = 0;
			return 0; //return because solution is already incorrect
		}
	}
}

// Check if digits 1-9 are present in ALL columns.
void* check_cols(void* param) {
	// Create one thread for each column.
	pthread_t tid[N];
	// Store information of curent coordinates.
	params *data = (params*)malloc(sizeof(params));
	for (int i=0; i<N; i++) {
		data->col = i;
		pthread_create(&tid[i], 0, check_col, data);
	}
	for (int i=0; i<N; i++) 
		pthread_join(tid[i], NULL);
}

// Check if digits 1-9 are present in single 3x3 box.
void* check_box(void* param) {
	params* data = param;
	int reqs[N] = {0,0,0,0,0,0,0,0,0};
	int n;
	int currRow = data->row;
	int currCol = data->col;
	// Determine which requirements (1-9) are present.
	for (int i=0; i<N; i++) {
		n = nums[currRow][currCol];
		currRow++;
		if (currRow % 3 == 0) {
			currRow = data->row;
			currCol++;
		}
		reqs[n-1] = 1;
	}
	// Return if a requirement is not present in box.
	for (int i=0; i<N; i++) {
		if (reqs[i] == 0) {
			solution = 0;
			return 0;
		}
	}
}

// Check if digits 1-9 are present in ALL 3x3 boxes.
void* check_boxes(void* param) {
	// Create one thread for each box.
	pthread_t tid[N];
	// Create counter variable.
	int i = 0;
	// Store information of current coordinates.
	params *data = (params*)malloc(sizeof(params));
	for (int row=0; row<N; row+=3) {
		for (int col=0; col<N; col+=3) {
			data->row = row;
			data->col = col;
			pthread_create(&tid[i], 0, check_box, data);
			i++;
		}
	}
	// Join each thread.
	for (i=0; i<N; i++) { 
		pthread_join(tid[i], NULL);
	}
}

// If user wants to check puzzle with one thread.
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

// If user wants to check puzzle with 27 threads.
void multi_thread () {	
	// Three threads, for rows/cols/boxes.
	pthread_t tid[3];
	// Create thread for checking cols.
	pthread_create(&tid[0], 0, check_cols, NULL);
	// Create thread for checking rows.
	pthread_create(&tid[1], 0, check_rows, NULL);
	// Create thread for checking boxes.
	pthread_create(&tid[2], 0, check_boxes, NULL);
	// Join threads.
	for (int i = 0; i < 3; i++) 
		pthread_join(tid[i], NULL);
}

int main (int argc, char** argv) {
	// Record the start time of program.
	clock_t t = clock();

	// Initialize sudoku array.
	get_input();

	// User enters 1 for single-thread, 2 for multi-thread.
	if (atoi(argv[1]) == 1)
		one_thread();
	else if (atoi(argv[1]) == 2)
		multi_thread();

	// Record the end time of program.
	t = clock() - t;
	double deltaT = ((double)t)/CLOCKS_PER_SEC;
	
	// Print out the sudoku board from the array.
	print_board(deltaT);
	
	return 0;
}
