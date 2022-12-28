all: compile link

compile:
	g++ -I Thirdparty/include -c src/main.cpp

link:
	g++ main.o -o main -L Thirdparty/lib -l sfml-network