all: rbt_test
rbt_test: rbt_test.o
			g++ -o rbt_test rbt_test.o

rbt_test.o: rbt.h
			g++ -c rbt_test.c

clean: 
			rm -f rbt_test *.o