default:
	g++ main.cpp -o main.exe -O2 --static -static-libgcc -static-libstdc++ -Wall -Wno-missing-braces -I raylib/include -L raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -I include
	./main.exe