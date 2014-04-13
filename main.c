#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "quicksort.h"
#include "arand.h"

#define RANDOMCOUNT (1000000)
#define MICROSECOND (1000000)

int randomvars[RANDOMCOUNT];
#define VARSCOUNT (5)
int vars[5] = {2, 3, 1, 1, 1};

void fillRandom(int *buf, int count);
int subTimeval(struct timeval *op1, struct timeval *op2, struct timeval *result);

int main(int argc, char **argv) {
	int i;
	struct timeval starttime, endtime, totaltime;

	arand_init(time(NULL));

	fillRandom(randomvars, RANDOMCOUNT);
/*	for(i = 0; i < RANDOMCOUNT; i++)
		printf("%i ", randomvars[i]);
	printf("\n");*/

	gettimeofday(&starttime, NULL);
	quickSort(randomvars, RANDOMCOUNT);
	gettimeofday(&endtime, NULL);
/*	for(i = 0; i < RANDOMCOUNT; i++)
		printf("%i ", randomvars[i]);
	printf("\n");*/
/*
	for(i = 0; i < VARSCOUNT; i++)
		printf("%i ", vars[i]);
	printf("\n");
	quickSort(vars, VARSCOUNT);
	for(i = 0; i < VARSCOUNT; i++)
		printf("%i ", vars[i]);
	printf("\n");
*/
	subTimeval(&endtime, &starttime, &totaltime);
/*	fprintf(stderr, "Start: %llis %ius\n", starttime.tv_sec, starttime.tv_usec);
	fprintf(stderr, "  End: %llis %ius\n", endtime.tv_sec, endtime.tv_usec);*/
	fprintf(stderr, "Total: %llis %ius\n", totaltime.tv_sec, totaltime.tv_usec);

	exit(EXIT_SUCCESS);
}

void fillRandom(int *buf, int count) {
	int i;

	for(i = 0; i < count; i++)
		arand_random32(&buf[i], 32);
}

int subTimeval(struct timeval *op1, struct timeval *op2, struct timeval *result) {
	if(op1 == NULL || op2 == NULL || result == NULL)
		return(-1);

	result->tv_sec = op1->tv_sec - op2->tv_sec;
	if(op2->tv_usec > op1->tv_usec) {
		result->tv_sec--;
		result->tv_usec = MICROSECOND - (op2->tv_usec - op1->tv_usec);
	} else {
		result->tv_usec = op1->tv_usec - op2->tv_usec;
	}

	return(0);
}
