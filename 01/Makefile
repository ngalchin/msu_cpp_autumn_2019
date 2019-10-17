all: calc

calc: calculator.o
	-@g++ -o calc calculator.o --std=c++14

calculator.o: calculator.cpp
	-@g++ -c calculator.cpp --std=c++14

run:
	-@./calc $(arg)

test: test.py
	@python3 test.py

clean:
	-@rm -rf *.o run
