default:
	g++ main.cpp -o main.exe -O2 --static -static-libgcc -static-libstdc++ -Wno-missing-braces -I raylib/include -lraylib -L raylib/lib/ -lopengl32 -lgdi32 -lwinmm -I include/
	./main.exe