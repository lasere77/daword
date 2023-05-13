CXX = g++
EXEC = main.exe

build: compileSource compileObject
start: compileSource compileObject run clearObject

compileSource: src/Main.cpp
	$(CXX) -c src/*.cpp -I"libs\SFML-2.5.1\include"

compileObject: Main.o
	$(CXX) *.o -o bin/$(EXEC) -L"libs\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: bin/$(EXEC)
	./bin/$(EXEC)

clearObject:
	rm *.o

copyDll: libs/SFML-2.5.1/bin/
	cp libs/SFML-2.5.1/bin/*.dll bin/