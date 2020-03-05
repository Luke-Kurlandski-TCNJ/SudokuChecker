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

void luke() {
	int nums[N][N];
	get_input(nums);
	for (int j=0; j<N; j++) {
		for (int i=0; i<N; i++) {
			printf("%d", nums[i][j]);
		}
		printf("\n");
	}	
}

int main (int argc, char** argv) {
	luke();	
}


int method() {

}
