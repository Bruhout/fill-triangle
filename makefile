VERSION = c++11

all: build/b_coords build/conditional build/scanline build/vec3d.o
	echo "BUILD FINISHED"
	
build/b_coords: src/b_coords.cpp build/vec3d.o
	g++ -o build/b_coords src/b_coords.cpp build/vec3d.o -g --std=$(VERSION)

build/scanline: src/scanline.cpp build/vec3d.o
	g++ -o build/scanline src/scanline.cpp build/vec3d.o -g --std=$(VERSION)

build/conditional: src/conditional.cpp build/vec3d.o
	g++ -o build/conditional src/conditional.cpp build/vec3d.o -g --std=$(VERSION)

build/vec3d.o: src/vec3d.cpp
	g++ -o build/vec3d.o src/vec3d.cpp -g --std=$(VERSION) -c

runall: build/b_coords build/conditional build/scanline
	./build/b_coords
	./build/conditional
	./build/scanline
