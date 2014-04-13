OBJS   = quicksort.o arand.o main.o 
TARGET = test
CFLAGS = -O3 -pedantic -Wall -Wextra  -std=gnu99

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: clean
