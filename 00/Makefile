all: my_prog_1 my_prog_2


my_prog_1: sum_by_rows.o
	-@g++ -o my_prog_1 sum_by_rows.o --std=c++11 -O2

sum_by_rows.o:
	-@g++ -c sum_by_rows.cpp --std=c++11 -O2

my_prog_2: sum_by_columns.o
	-@g++ -o my_prog_2 sum_by_columns.o --std=c++11 -O2

sum_by_columns.o:
	-@g++ -c sum_by_columns.cpp --std=c++11 -O2

run: run_1 run_2

run_1:
	-@./my_prog_1

run_2:
	-@./my_prog_2

clean:
	-@rm -rf *.o run
