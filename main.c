#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
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
void printAll(int *values, int count);

int main(int argc, char **argv) {
	struct timeval starttime, endtime, totaltime;

	arand_init(time(NULL));

	fprintf(stderr, "  Stack: ");
	fillRandom(randomvars, RANDOMCOUNT);
	gettimeofday(&starttime, NULL);
	quickSort(randomvars, RANDOMCOUNT, QS_COPY_STACK);
	gettimeofday(&endtime, NULL);
	subTimeval(&endtime, &starttime, &totaltime);
	fprintf(stderr, "%llis %ius\n", totaltime.tv_sec, totaltime.tv_usec);

	fprintf(stderr, " Malloc: ");
	fillRandom(randomvars, RANDOMCOUNT);
	gettimeofday(&starttime, NULL);
	quickSort(randomvars, RANDOMCOUNT, QS_COPY_MALLOC);
	gettimeofday(&endtime, NULL);
	subTimeval(&endtime, &starttime, &totaltime);
	fprintf(stderr, "%llis %ius\n", totaltime.tv_sec, totaltime.tv_usec);

	fprintf(stderr, "Inplace: ");
	fillRandom(randomvars, RANDOMCOUNT);
//	printAll(randomvars, RANDOMCOUNT);
	gettimeofday(&starttime, NULL);
	quickSort(randomvars, RANDOMCOUNT, QS_INPLACE);
	gettimeofday(&endtime, NULL);
//	printAll(randomvars, RANDOMCOUNT);
	subTimeval(&endtime, &starttime, &totaltime);
	fprintf(stderr, "%llis %ius\n", totaltime.tv_sec, totaltime.tv_usec);

	exit(EXIT_SUCCESS);
}

void fillRandom(int *buf, int count) {
	int i;

	for(i = 0; i < count; i++)
		arand_random32(&((uint32_t *)buf)[i], 32);
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

void printAll(int *values, int count) {
	int i;

	for(i = 0; i < count; i++)
		printf("%i ", values[i]);
	printf("\n");
}
