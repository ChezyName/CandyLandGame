all: icon compile link

icon:
	windres src/Icons/Candyland.rc -O coff -o src/Icons/Candyland.res

compile:
	g++ -I Thirdparty/include -c src/main.cpp

link:
#DebugMode
#	g++ main.o -o CandylandClient/Candyland -L Thirdparty/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-network src/Icons/Candyland.res
#Prod
	g++ main.o -g -o CandylandClient/Candyland -L Thirdparty/lib -mwindows -l sfml-graphics -l sfml-window -l sfml-system -l sfml-network -static-libgcc -static-libstdc++ -mwindows src/Icons/Candyland.res


.PHONY: clean
clean:
	del main.o