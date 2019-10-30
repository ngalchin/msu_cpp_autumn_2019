all: matr

matr: matr.o matr_main.o
	-@g++ -o matr matr.o matr_main.o --std=c++14

matr.o: matr.cpp matr.h
	-@g++ -c matr.cpp --std=c++14

matr_main.o: matr_main.cpp
	-@g++ -c matr_main.cpp --std=c++14

run:
	-@./matr

test:
	-@./matr

clean:
	-@rm -rf *.o
