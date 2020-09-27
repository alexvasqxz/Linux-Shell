// 
//  pi_calculation.c
//  
//  This program written in C when run on terminal
//  asks for a number of threads to create and then 
//  uses the monte_carlo algorithm for pi estimation
//  creating a total of 10,000 points where each thread 
//  works (10,000/number of threads) points
//
//   Created on 9/27/20
//   Copyright © 2020 Gustavo Vasquez. All rights reserved
//
//           ___________________________________
//          |                                   |
//          |              WELCOME              |
//          |              ARE YOU              |
//          |              READY TO             |
//          |            ESTIMATE THE           |
//          |            VALUE OF PI?           |
//          |                                   |
//          |          -Gustavo Vasquez         |
//          |                                   |
//          |___________________________________|
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


/* R2
// Method that creates a random number (which later will
// be the position of each point) within the [0,1] range
//
// Return: A random value in the [0,1] range
// */

int numberThreads;
int pointsPerThread;
long pointsInCircle;
unsigned int seed;

double rndm(){
	return (double)rand_r(&seed) / (double)((unsigned)RAND_MAX +1);
}

/* MonteCarlo
// Function that uses the Monte Carlo method for the 
// estimation of a pi value with points within a circle
//
*/
void *monteCarlo(void* t_id){
	double x, y;
	int *count = (int *)malloc(sizeof(int));
	*count = 0;
	
	for (int i = 0; i < pointsPerThread; i++){
		x = rndm();
		y = rndm();
		if((x-.5)*(x-.5) + (y-.5)*(y - .5) <= .25){ //0.25 = sqrt(0.5) = r^2
			*count += 1;
		}
	}
	pthread_exit((void *) count);
}



int main(int argc, char* argv[]){
	clock_t begin = clock(); // We start our timer
	seed = time(NULL);
	int points = 10000; // 10,000 points in this example
	
	numberThreads = atoi(argv[1]);
	if (numberThreads < 1){
		printf("Number of threads must be greater than 0\n");
		exit(1);
	}
	
	// We'll start the real algorithm
	printf(" --------------------------------------\n"
		   "Working with %d threads \n"
		   "And %d points \n"
		" -------------------------------------\n", numberThreads, points);
	
	double pi;
	void *countPerThread;
	int threadArr;
	
	// Array of threads
	pthread_t threads[numberThreads];
	pointsPerThread = points / numberThreads;
	
	unsigned int i = 0;
	for (i = 0; i < numberThreads; i++){
		threadArr = pthread_create(&threads[i], NULL, monteCarlo, (void *)(intptr_t) i);
		seed++;
	}
	
	// Wait for each thread to
	// be completed using 
	// thread_join()
	//

	for(i=0; i<numberThreads; i++){
        	pthread_join(threads[i], &countPerThread);
        	pointsInCircle += * (long *) countPerThread;
    	}	
	
	printf(" --------------------------------------\n"
		   "Points in circle: %zd\n", pointsInCircle);
	
	// We get the estimation of pi base on the equation seen in
	// class (pi = (4 * (pointsInCircle / points))
	//
	
	pi = (4.00 * (float)pointsInCircle / (float)points);
	
	printf ("\nThe estimation ontained for the value of pi is: %0.5f\n", pi);
	clock_t end = clock(); // Stop timer
    	double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    	printf("-------------------------------------------------\n"
           	"Time used with %d threads: %.3f\n", numberThreads, time_spent);
	exit(0);
}
