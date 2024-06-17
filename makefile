all: src/b_coords.cpp src/conditional.cpp src/scanline.cpp build/vec3d.o
	g++ -o build/b_coords src/b_coords.cpp build/vec3d.o -g
	g++ -o build/scanline src/scanline.cpp build/vec3d.o -g
	g++ -o build/conditional src/conditional.cpp build/vec3d.o -g

build/b_coords: src/b_coords.cpp build/vec3d.o
	g++ -o build/b_coords src/b_coords.cpp build/vec3d.o -g

build/scanline: src/scanline.cpp build/vec3d.o
	g++ -o build/scanline src/scanline.cpp build/vec3d.o -g

build/conditional: src/conditional.cpp build/vec3d.o
	g++ -o build/conditional src/conditional.cpp build/vec3d.o -g

build/vec3d.o: src/vec3d.cpp
	g++ -o build/vec3d.o src/vec3d.cpp -g -c

runall: build/b_coords build/conditional build/scanline
	./build/b_coords
	./build/conditional
	./build/scanline
