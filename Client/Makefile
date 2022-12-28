all: compile link

compile:
	g++ -I Thirdparty/include -c src/main.cpp

link:
#DebugMode
	g++ main.o -o Candyland -L Thirdparty/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-network
#Prod
#	g++ main.o -o Candyland -L Thirdparty/lib -mwindows -l sfml-graphics -l sfml-window -l sfml-system -l sfml-network