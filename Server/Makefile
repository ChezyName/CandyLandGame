all: icon compile link

icon:
	windres src/Icon/Candyland.rc -O coff -o src/Icon/Candyland.res

compile:
	g++ -I Thirdparty/include -c src/main.cpp

link:
	g++ main.o -o CandylandServer/CandylandServer -L Thirdparty/lib -l sfml-network src/Icon/Candyland.res