make:
	g++ -O3 main.cpp cell.cpp matrix_stuff.cpp -L/usr/lib/ -lSDL2main -lSDL2 -lSDL2_image -I/usr/include/SDL2 -D_REENTRANT
	./a.out
