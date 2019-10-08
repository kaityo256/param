all: a.out

a.out: test.cpp ../param.hpp
	g++ -Wall -Wextra -std=c++11 test.cpp

.PHONY: clean

clean:
	rm -f a.out
