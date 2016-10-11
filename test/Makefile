.PHONY: test
LD_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
CXX_FLAGS=--std=c++14 -Wall -Wextra -pedantic -pthread -O3
IN_FLAGS=../src

test:
	g++ -g $(LD_FLAGS) -I $(IN_FLAGS) $(CXX_FLAGS) main.cpp
