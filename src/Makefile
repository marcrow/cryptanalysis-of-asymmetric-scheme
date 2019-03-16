CC=g++
CFLAGS=-Wall -Wextra -lpthread -lgmp -lgmpxx -std=c++11
EXEC=../exec

all: $(EXEC)

$(EXEC): main.o Elliptique.o Point.o FactorisationElliptique.o QuadraSieve.o matriceNullSpace.o
	$(CC) -o $(EXEC) $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f *.o
	rm -f *.txt
mr: clean
	rm -f $(EXEC)
