# Declaratiile de variabile
CC = gcc
CFLAGS = -std=c11 -g -Wall -lm
 
# Regula de compilare
all: build

build: task1.c task2.c task3.c task4.c 
	$(CC) -o task1 task1.c $(CFLAGS)

	$(CC) -o task2 task2.c $(CFLAGS)

	$(CC) -o task3 task3.c $(CFLAGS)

	$(CC) -o task4 task4.c $(CFLAGS)


# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f task1 task2 task3 task4
	rm -f *.out
	rm my_diff
