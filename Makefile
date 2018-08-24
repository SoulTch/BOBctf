all: bin
bin: main.cpp
	g++ -no-pie -o bin main.cpp

