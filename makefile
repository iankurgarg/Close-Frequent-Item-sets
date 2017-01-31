FILENAME=T10I4D100K.dat
MINSUP=5

default: main.cpp FPTree.cpp list.cpp FPTree.h list.h transaction.cpp transaction.h itemsetfrequency.h itemsetfrequency.cpp database.h database.cpp
	g++ main.cpp FPTree.cpp list.cpp transaction.cpp itemsetfrequency.cpp database.cpp -o main
	./main $(FILENAME) $(MINSUP)

clean:
	rm main
