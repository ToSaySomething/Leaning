OBJ = main.o mytool1.o mytool2.o
make: $(OBJ)
	gcc -o main $(OBJ)
main.o: main.c mytool1.c mytool2.c
	gcc -c main.c
mytool1.o: mytool1.c mytool1.h
	gcc -c mytool1.c
mytool2.o: mytool2.c mytool2.h
	gcc -c mytool2.c

clean: 
	rm -f main $(OBJ)



