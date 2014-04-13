typedef enum {
	QS_INPLACE,
	QS_COPY_MALLOC,
	QS_COPY_STACK
} QSMode;

int quickSort(int *values, int count, QSMode mode);

