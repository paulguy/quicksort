#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "quicksort.h"

static inline int compar(const void *op1, const void *op2) {
	return(*(int *)op1 - *(int *)op2); /* return positive if op1 > op2 */
}

static inline void swap(void *val1, void *val2, int size) {
	int swap[size];

	if(val1 == val2) return;
	memcpy(swap, val1, size);
	memcpy(val1, val2, size);
	memcpy(val2, swap, size);
}

static void __quickSort_inplace(void *values, int count, int size, int (*compar)(const void *, const void *)) {
	int i, j;
	int pivotloc, pivotend;
	void *pivotval;
	int offset;

	if(count < 2) {
		return;
	} else if (count == 2) {
/*		for(j = 0; j < count; j++)
			printf("%i ", ((int *)values)[j]);
		printf("-> ");*/

		if(compar(&values[0], &values[size]) > 0)
			swap(&values[0], &values[size], size);

/*		for(j = 0; j < count; j++)
			printf("%i ", ((int *)values)[j]);
		printf("\n");*/
	} else {
/*		for(j = 0; j < count; j++)
			printf("%i ", ((int *)values)[j]);
		printf("-> ");*/

		pivotloc = (count - 1) * size;
		pivotend = (count - 1) * size;
		pivotval = &values[pivotloc];
		offset = 0;

		while(offset < pivotloc) {
			if(compar(&values[offset], pivotval) > 0) {
				swap(&values[offset], &values[pivotloc - size], size);
				swap(&values[pivotloc - size], &values[pivotend], size);
				pivotloc -= size; pivotval -= size;
				pivotend -= size;
			} else if(compar(&values[offset], pivotval) == 0) {
				swap(&values[offset], &values[pivotloc - size], size);
				pivotloc -= size; pivotval -= size;
			} else {
				offset += size;
			}
		}

/*		for(j = 0; j < count; j++)
			printf("%i ", ((int *)values)[j]);
		printf("\n");*/

		__quickSort_inplace(values, pivotloc / size, size, compar);
		__quickSort_inplace(&values[pivotend], count - (pivotend / size), size, compar);
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
			swap(&values[0], &values[1], sizeof(int));
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
			} else if(values[i] == pivotVal) {
				continue;
			} else { /* > */
				right[rightIndex] = values[i];
				rightIndex++;
			}
		}

		memcpy(values, left, leftIndex * sizeof(int));
		for(i = leftIndex; i < count - rightIndex; i++)
			values[i] = pivotVal;
		memcpy(&values[count - rightIndex], right, rightIndex * sizeof(int));
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
		} else if(values[i] == pivotVal) {
			continue;
		} else { /* > */
			right[rightIndex] = values[i];
			rightIndex++;
		}
	}

	memcpy(values, left, *leftIndex * sizeof(int));
	for(i = *leftIndex; i < count - rightIndex; i++)
		values[i] = pivotVal;
	memcpy(&values[count - rightIndex], right, rightIndex * sizeof(int));
}

static void __quickSort_copy_stack(int *values, int count) {
	int leftIndex;
//	int j;

	if(count < 2) {
		return;
	} else if(count == 2) {
		if(values[0] > values[1])
			swap(&values[0], &values[1], sizeof(int));
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

int quickSort(void *values, int count, int size, QSMode mode) {
	if(count < 2 || values == NULL) {
		return(-1);
	}

	switch(mode) {
		case QS_INPLACE:
			__quickSort_inplace(values, count, size, compar);
			break;
/*		case QS_COPY_MALLOC:
			__quickSort_copy_malloc(values, count);
			break;
		case QS_COPY_STACK:
			__quickSort_copy_stack(values, count);
			break;*/
		case QS_GLIBC:
			qsort(values, count, size, compar);
			break;
	}

	return(0);
}

