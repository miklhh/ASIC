CC = g++
CFLAGS = -O2 -std=c++20 -Wall -Wextra -Wpedantic -Weffc++

.PHONY: run-all clean

run-all: test_graph.out test_sfg.out
	./test_graph.out
	./test_sfg.out

test_graph.out: test_graph.cc catch.o ../graph.h ../trait.h
	${CC} ${CFLAGS} test_graph.cc catch.o -o $@

test_sfg.out: test_sfg.cc catch.o ../sfg.h ../op.h ../graph.h
	${CC} ${CFLAGS} test_sfg.cc catch.o -o $@

catch.o: catch.cc catch.hpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rvf *.o *.out
