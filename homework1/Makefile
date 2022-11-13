# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm
 
# Regula de compilare
all: problema1 problema2 problema3 problema4

problema1: problema1.c
	$(CC) -o problema1 problema1.c $(CFLAGS)

problema2: problema2.c
	$(CC) -o problema2 problema2.c $(CFLAGS)

problema3: problema3.c
	$(CC) -o problema3 problema3.c $(CFLAGS)

problema4: problema4.c
	$(CC) -o problema4 problema4.c $(CFLAGS)


# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f problema1 problema2 problema3 problema4
	rm -f *.out
	rm my_diff
