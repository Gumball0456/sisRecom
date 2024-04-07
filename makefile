sisRecom: sisRecom.o matriz_utils.o
	gcc -o sisRecom sisRecom.o matriz_utils.o

sisRecom.o: sisRecom.c matriz_utils/matriz_utils.h
	gcc -g -c sisRecom.c

matriz_utils.o: matriz_utils/matriz_utils.c matriz_utils/matriz_utils.h
	gcc -g -c matriz_utils/matriz_utils.c

clean:
	rm *.o sisRecom
