#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int **get_input() {
	FILE *f = fopen("input.txt", "r");
	if (f==NULL) 
		printf("Error Opening input.txt\n");
	
	int nums[9][9];
	int d; 
	fscanf(f, "%d", d);
	print("%d", d);
	/*
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			fscanf(f, "%d", &nums[i][j]);
		}
	}
	*/
	fclose(f);
	return nums;
}

int main (int argc, char** argv) {
	
}

void luke() {
	int n = get_input();
}

int method() {

}
