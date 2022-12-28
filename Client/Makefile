all: compile link

compile:
	g++ -I Thirdparty/include -c src/main.cpp

link:
	g++ main.o -o main -L Thirdparty/lib -mwindows -l sfml-graphics -l sfml-window -l sfml-system -l sfml-network