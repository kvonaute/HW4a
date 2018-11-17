#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void printMatrix(int *matrix, int w, int h){
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			fprintf(stderr,"%i\t",matrix[i*w+j]);
		}
		fprintf(stderr,"\n\n");
	}
}


void transp(int *matrix, int *newMatrix, int w, int h, int blocksize){
	for(int i = 0; i < h; i += blocksize){
		for(int j = 0; j < w; j += blocksize){
			for(int x = i; x < i + blocksize; ++x){
				for(int y = j; y < j + blocksize; ++y){
					//int temp = matrix[x + y * dim];
					//printf("%d\n", temp);
					//int temp = -1;
					if(y + x * w < w * h && x + y * h < w * h)
						newMatrix[x + y * h] = matrix[y + x * w];
				}
			}
		}
	}
}

int main(int argc, char **argv){
	if (argc != 4){
		fprintf(stderr, "Usage: transp matrixwidth matrixheight blocksize\n");
		exit(-1);
	}

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int blocksize = atoi(argv[3]);

	int *matrix = (int*)malloc(width * height *sizeof(int));
	int *newMatrix = (int*)malloc(width*height*sizeof(int));

	for(int i = 0; i < width * height; i++){
		matrix[i] = rand()/(RAND_MAX/100);
	}

	//fprintf(stderr,"Input matrix:\n");
	//printMatrix(matrix, width, height);

	struct timeval tv;
	time_t starttime_seconds, starttime_microseconds, endtime_seconds, endtime_microseconds;

	gettimeofday(&tv, NULL);
	starttime_seconds = tv.tv_sec;
	starttime_microseconds = tv.tv_usec;

	transp(matrix, newMatrix, width, height, blocksize);

	gettimeofday(&tv, NULL);
	endtime_seconds = tv.tv_sec;
	endtime_microseconds = tv.tv_usec;

	//fprintf(stderr,"Output matrix:\n");
	//printMatrix(newMatrix, height, width);


	long timetotal = (endtime_seconds - starttime_seconds) * 1000000 + (endtime_microseconds
					-starttime_microseconds);
	printf("%d %d %d %ld\n", width, height, blocksize, timetotal);

	free(matrix);
	free(newMatrix);
}
