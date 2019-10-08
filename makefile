all: a.out

a.out: test.cpp param.hpp
	g++ -Wall -Wextra test.cpp

.PHONY: clean

clean:
	rm -f a.out
