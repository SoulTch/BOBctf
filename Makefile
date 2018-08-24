all: bin
bin: main.cpp
	g++ -no-pie -o bin main.cpp
hack: hack.cpp
	g++ -lthread hack.cpp
