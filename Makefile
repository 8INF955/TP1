.PHONY: app
LD_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
CXX_FLAGS=--std=c++14 -Wall -Wextra -pedantic
IN_FLAGS=src

app:
	g++ $(LD_FLAGS) -I $(IN_FLAGS) $(CXX_FLAGS) src/main.cpp
