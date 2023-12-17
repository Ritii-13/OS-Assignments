CC = gcc
CFLAGS = -pthread -Wall
TARGETS = Q1 Q2 Q3

all: $(TARGETS)

Q1: Q1.c
	$(CC) $(CFLAGS) -o Q1 Q1.c

Q2: Q2.c
	$(CC) $(CFLAGS) -o Q2 Q2.c -lpthread

Q3: Q3.c
	$(CC) $(CFLAGS) -o Q3 Q3.c -lpthread

clean:
	rm -f $(TARGETS)
