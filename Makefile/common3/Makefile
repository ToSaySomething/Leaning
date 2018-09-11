CC = gcc
OBJ = main.o mytool1.o mytool2.o

make: $(OBJ)
	$(CC) -o main $(OBJ)
main.o: mytool1.h mytool2.h
mytool1.o: mytool1.h
mytool2.o: mytool2.h

.PHONY: clean
clean:
	rm -f main $(OBJ)



