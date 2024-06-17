#include <iostream>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include "../include/vec3d.h"

// This file will help you understand the scanline triangle drawing algorithm.
// This is only a half implementation.
// The remanining part of the algorithm is very simialar and is left as an exercise to the learner.

void FillTriangle(Vec3D v1 , Vec3D v2 , Vec3D v3 , unsigned char* image , int image_width , int image_height);

int main(void)
{
    int image_width = 512;
    int image_height = 512;
    int bytes_per_pixel = 3;
    int image_size = image_height * image_width * bytes_per_pixel;

    unsigned char* output_image = (unsigned char*)malloc(image_size);

    if (output_image == NULL) {
        std::cerr << "failed to allocate memory for the image\n";
    }

    // Initialize the image to a dark gray color
    for (int i=0 ; i<image_size ; i++) {
        *(output_image + i) = 50;
    }

	Vec3D v1 = {0.5 , 0.2 , 0};
	Vec3D v2 = {0.7 , 0.5 , 0};
	Vec3D v3 = {0.3 , 0.8 , 0};

    FillTriangle(v1 , v2 , v3 , output_image , image_width , image_height);
    stbi_write_jpg("scanline.jpg" , image_width , image_height , bytes_per_pixel , output_image , 100);
}


void FillTriangle(Vec3D v1 , Vec3D v2 , Vec3D v3 , unsigned char* image , int image_width , int image_height)
{
    // VERTICES ARE GIVEN AS NORMAL COORDINATES BETWEEN 0 AND 1
    // First, we sort the vertices based on y coordinate
    if (v1.y > v2.y) {
        std::swap(v1 , v2);
    }

    if (v1.y > v3.y) {
        std::swap(v1 , v3);
    }

    if (v2.y > v3.y) {
        std::swap(v2 , v3);
    }

	double pixel_height = 1/(double)image_height;
	double pixel_width = 1/(double)image_width;

    // {x1 , y1} is on top , {x3 , y3} is on the bottom

    //y_diff is always positive
    // The two slope values correspond to the slopes of the 2 sides of the triangle going down from {x1 , y1}
    double slope_a = (v2.y - v1.y) / (v2.x - v1.x);
    double slope_b = (v3.y - v1.y) / (v3.x - v1.x);

    for (double i=v1.y ; i<v2.y ; i+=pixel_height)
    {
        double x_offset_a = (i - v1.y) / slope_a;
        double x_offset_b = (i - v1.y) / slope_b;

		// OFFSET_B IS TO THE LEFT OF OFFSET_A
		if(x_offset_a < x_offset_b) {
            std::swap(x_offset_b , x_offset_a);
        }

		int x_coord;
		int y_coord;
        for (double j=v1.x+x_offset_b ; j < v1.x+x_offset_a ; j+=pixel_width)
        {
			x_coord = (int)(j * image_width);
			y_coord = (int)(i * image_height);

            *(image + (y_coord*image_width + x_coord)*3) = 200;
            *(image + (y_coord*image_width + x_coord)*3 + 1) = 200;
            *(image + (y_coord*image_width + x_coord)*3 + 2) = 200;
        }
    }

	slope_a = (v2.y - v3.y) / (v2.x - v3.x);
	slope_b = (v1.y - v3.y) / (v1.x - v3.x);
	for (double i=v3.y ; i>v2.y ; i-=pixel_height)
	{
		double x_offset_a = (i - v3.y) / slope_a;
		double x_offset_b = (i - v3.y) / slope_b;

		// OFFSET_B IS TO THE LEFT OF OFFSET_A
		if (x_offset_a < x_offset_b) {
			std::swap(x_offset_a , x_offset_b);
		}

		int x_coord;
		int y_coord;
		for (double j=v3.x+x_offset_b ; j<v3.x+x_offset_a ; j+=pixel_width)
		{
			x_coord = (int)(j * image_width);
			y_coord = (int)(i * image_height);
		
            *(image + (y_coord*image_width + x_coord)*3) = 200;
            *(image + (y_coord*image_width + x_coord)*3 + 1) = 200;
            *(image + (y_coord*image_width + x_coord)*3 + 2) = 200;
		}
	}
}
