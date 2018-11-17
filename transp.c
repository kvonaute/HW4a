#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

//one more change...

void printMatrix(int *matrix, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			fprintf(stderr,"%i\t",matrix[i*size+j]);
		}
		fprintf(stderr,"\n\n");
	}
}


void transp(int *matrix, int *newMatrix, int dim, int blocksize){
	for(int i = 0; i < dim; i += blocksize){
		for(int j = 0; j < dim; j += blocksize){
			for(int x = i; x < i + blocksize; ++x){
				for(int y = j; y < j + blocksize; ++y){
					//int temp = matrix[x + y * dim];
					//printf("%d\n", temp);
					//int temp = -1;
					newMatrix[x + y * dim] = matrix[y + x * dim];
				}
			}
		}
	}
}

int main(int argc, char **argv){
	if (argc != 3){
		fprintf(stderr, "Usage: transp matrixwidth blocksize\n");
		exit(-1);
	}

	int dim = atoi(argv[1]);
	int blocksize = atoi(argv[2]);

	int *matrix = (int*)malloc(dim * dim *sizeof(int));
	int *newMatrix = (int*)malloc(dim*dim*sizeof(int));

	for(int i = 0; i < dim * dim; i++){
		matrix[i] = rand()/(RAND_MAX/100);
	}

//	fprintf(stderr,"Input matrix:\n");
//	printMatrix(matrix, dim);

	struct timeval tv;
	time_t starttime_seconds, starttime_microseconds, endtime_seconds, endtime_microseconds;

	gettimeofday(&tv, NULL);
	starttime_seconds = tv.tv_sec;
	starttime_microseconds = tv.tv_usec;

	transp(matrix, newMatrix, dim, blocksize);

	gettimeofday(&tv, NULL);
	endtime_seconds = tv.tv_sec;
	endtime_microseconds = tv.tv_usec;

//	fprintf(stderr,"Output matrix:\n");
//	printMatrix(newMatrix, dim);


	long timetotal = (endtime_seconds - starttime_seconds) * 1000000 + (endtime_microseconds
					-starttime_microseconds);
	printf("%d %d %ld\n",dim , blocksize, timetotal);

	free(matrix);
	free(newMatrix);
}
