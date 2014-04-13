#include <stdlib.h>
#include <stdio.h>

static inline void swap(int *val1, int *val2) {
	int swap;

	swap = *val1;
	*val1 = *val2;
	*val2 = swap;
}

static inline int findGreaterOrEqual(int *values, int count, int value) {
	int i;
	for(i = 0; i < count; i++) {
		if(values[i] >= value)
			return(i);
	}

	return(-1);
}

static void __quickSort(int *values, int count) {
	int i, j;
	int greateridx;
	int pivotloc;


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

		for(i = count - 1; i > 0; i--) {
			if(values[i - 1] > values[pivotloc]) {
				swap(&values[i - 1], &values[pivotloc]);
				pivotloc--;
			} else if(values[i - 1] == values[pivotloc]) {
				continue;
			} else if(values[i - 1] < values[pivotloc]) {
				greateridx = findGreaterOrEqual(values, i - 1, values[pivotloc]);
				if(greateridx == -1) { /* no greater values to the left */
					break;
				} else {
					swap(&values[greateridx], &values[i - 1]);
					swap(&values[i - 1], &values[pivotloc]);
					pivotloc--;
				}
			}
		}

/*		for(j = 0; j < count; j++)
			printf("%i ", values[j]);
		printf("\n");*/

		__quickSort(values, pivotloc);
		__quickSort(&values[pivotloc], count - pivotloc);
	}
}

int quickSort(int *values, int count) {
	if(count < 2 || values == NULL) {
		return(-1);
	}

	__quickSort(values, count);
}

