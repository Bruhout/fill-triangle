VERSION = c++11

all: build/b_coords build/conditional build/scanline build/conditional_bounded build/b_coords_bounded build/vec3d.o build/bounding_box.o
	echo "BUILD FINISHED"



build/b_coords: src/b_coords.cpp build/vec3d.o
	g++ -o build/b_coords src/b_coords.cpp build/vec3d.o -g --std=$(VERSION)

build/b_coords_bounded: src/b_coords_bounded.cpp build/vec3d.o build/bounding_box.o
	g++ -o build/b_coords_bounded src/b_coords_bounded.cpp build/vec3d.o build/bounding_box.o -g --std=$(VERSION)




build/conditional: src/conditional.cpp build/vec3d.o build/bounding_box.o
	g++ -o build/conditional src/conditional.cpp build/vec3d.o build/bounding_box.o -g --std=$(VERSION)

build/conditional_bounded: src/conditional_bounded.cpp build/vec3d.o build/bounding_box.o
	g++ -o build/conditional_bounded src/conditional_bounded.cpp build/vec3d.o build/bounding_box.o 



build/scanline: src/scanline.cpp build/vec3d.o
	g++ -o build/scanline src/scanline.cpp build/vec3d.o -g --std=$(VERSION)




build/vec3d.o: src/vec3d.cpp
	g++ -o build/vec3d.o src/vec3d.cpp -g --std=$(VERSION) -c

build/bounding_box.o: src/bounding_box.cpp
	g++ -o build/bounding_box.o src/bounding_box.cpp --std=$(VERSION) -c

runall: build/b_coords build/conditional build/scanline build/b_coords_bounded build/conditional_bounded
	./build/b_coords
	./build/conditional
	./build/scanline
	./build/b_coords_bounded
	./build/conditional_bounded
