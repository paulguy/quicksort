typedef enum {
	QS_INPLACE,
/*	QS_COPY_MALLOC,
	QS_COPY_STACK,*/
	QS_GLIBC
} QSMode;

int quickSort(void *values, int count, int size, QSMode mode);
