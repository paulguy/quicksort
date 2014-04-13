#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "quicksort.h"

static inline void swap(int *val1, int *val2) {
	int swap;

	swap = *val1;
	*val1 = *val2;
	*val2 = swap;
}

static void __quickSort_inplace(int *values, int count) {
	int i, j;
	int pivotloc, pivotend, pivotval;

	if(count < 2) {
		return;
	} else if (count == 2) {
/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("-> ");*/

		if(values[0] > values[1])
			swap(&values[0], &values[1]);

/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("\n");*/
	} else {
/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("-> ");*/

		pivotloc = count - 1;
		pivotend = count - 1;
		pivotval = values[pivotloc];

		for(i = 0; i < pivotloc; i++) {
			if(values[i] > pivotval) {
				swap(&values[i], &values[pivotloc - 1]);
				swap(&values[pivotloc - 1], &values[pivotend]);
				i--; /* need to evaluate the same spot again */
				pivotloc--;
				pivotend--;
			} else if(values[i] == pivotval) {
				swap(&values[i], &values[pivotloc - 1]);
				i--; /* need to evaluate the same spot again */
				pivotloc--;
			} else if(values[i] < pivotval) {
				continue;
			}
		}
		pivotloc = pivotend;

/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("\n");*/

		__quickSort_inplace(values, pivotloc);
		__quickSort_inplace(&values[pivotloc], count - pivotloc);
	}
}

static void __quickSort_copy_malloc(int *values, int count) {
	int *left;
	int *right;
	int leftIndex;
	int rightIndex;
	int pivotVal;
	int i, j;

	if(count < 2) {
		return;
	} else if(count == 2) {
		if(values[0] > values[1])
			swap(&values[0], &values[1]);
	} else {
/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("-> ");*/

		left = malloc(sizeof(int) * count);
		right = malloc(sizeof(int) * count);
		if(left == NULL || right == NULL)
			return; /* no way to report back, so just do nothing... */

		leftIndex = 0;
		rightIndex = 0;
		pivotVal = values[count - 1];

		for(i = 0; i < count - 1; i++) {
			if(values[i] < pivotVal) {
				left[leftIndex] = values[i];
				leftIndex++;
			} else {
				right[rightIndex] = values[i];
				rightIndex++;
			}
		}

		memcpy(values, left, leftIndex * sizeof(int));
		values[leftIndex] = pivotVal;
		memcpy(&values[leftIndex + 1], right, rightIndex * sizeof(int));
/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("\n");*/
		free(left);
		free(right);

		__quickSort_copy_malloc(values, leftIndex);
		__quickSort_copy_malloc(&values[leftIndex + 1], count - leftIndex - 1);
	}
}

static void __quickSort_copy_stack_part(int *values, int count, int *leftIndex) {
	int rightIndex;
	int pivotVal;
	int left[count];
	int right[count];
	int i;

	*leftIndex = 0;
	rightIndex = 0;
	pivotVal = values[count - 1];

	for(i = 0; i < count - 1; i++) {
		if(values[i] < pivotVal) {
			left[*leftIndex] = values[i];
			(*leftIndex)++;
		} else {
			right[rightIndex] = values[i];
			rightIndex++;
		}
	}

	memcpy(values, left, *leftIndex * sizeof(int));
	values[*leftIndex] = pivotVal;
	memcpy(&values[*leftIndex + 1], right, rightIndex * sizeof(int));
}

static void __quickSort_copy_stack(int *values, int count) {
	int leftIndex;
//	int j;

	if(count < 2) {
		return;
	} else if(count == 2) {
		if(values[0] > values[1])
			swap(&values[0], &values[1]);
	} else {
/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("-> ");*/
		__quickSort_copy_stack_part(values, count, &leftIndex);
/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("\n");*/

		__quickSort_copy_stack(values, leftIndex);
		__quickSort_copy_stack(&values[leftIndex + 1], count - leftIndex - 1);
	}
}

int quickSort(int *values, int count, QSMode mode) {
	if(count < 2 || values == NULL) {
		return(-1);
	}

	switch(mode) {
		case QS_INPLACE:
			__quickSort_inplace(values, count);
			break;
		case QS_COPY_MALLOC:
			__quickSort_copy_malloc(values, count);
			break;
		case QS_COPY_STACK:
			__quickSort_copy_stack(values, count);
			break;
	}

	return(0);
}

