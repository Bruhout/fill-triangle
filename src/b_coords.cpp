#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include "../include/vec3d.h"

bool get_b_coords(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D point , Vec3D* output);

int main(void)
{
    unsigned int width = 512;
    unsigned int height = 512;
    unsigned int bytes_per_pixel = 3;
    unsigned int image_size = width * height * bytes_per_pixel;

    double pixel_width = 1/(double)width;
    double pixel_height = 1/(double)height;

    unsigned char* image_data = (unsigned char*)malloc(image_size);

    Vec3D v1(0.5 , 0.2 , 0);
    Vec3D v2(0.7 , 0.5 , 0);
    Vec3D v3(0.3 , 0.8 , 0);

    Vec3D point;

    Vec3D b_coords;

	// START CLOCK
	std::chrono::_V2::system_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ;j<width ; j++)
        {
            point.x = (j / (double)width) + pixel_width/2;
            point.y = (i / (double)height) + pixel_height/2;

            if (get_b_coords(v1 , v2 , v3 , point , &b_coords)==true)
            {
                *(image_data + (i*width + j)*3 + 0) = 200;
                *(image_data + (i*width + j)*3 + 1) = 50;
                *(image_data + (i*width + j)*3 + 2) = 50;
            }
            else 
            {
                *(image_data + (i*width + j)*3 + 0) = 0;
                *(image_data + (i*width + j)*3 + 1) = 120;
                *(image_data + (i*width + j)*3 + 2) = 120;
            }
        }
    }
	
	// CALCULATE TIME TAKEN
	std::chrono::_V2::system_clock::time_point stop_time = std::chrono::high_resolution_clock::now();

	std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
	std::cout << "Time taken by b_coords was :"<< duration.count() << " microseconds" << '\n';

    stbi_write_jpg("b_coords.jpg" , width , height , bytes_per_pixel , image_data , 100);
}


double get_tri_area(Vec3D v1 , Vec3D v2 , Vec3D v3)
{
    Vec3D side12 = v2 - v1;
    Vec3D side23 = v3 - v2;
    Vec3D side31 = v1 - v3;

    double height = ((side12*-1) - (side12 * -1).ProjectOnto(side23)).Magnitude();
    return height * side23.Magnitude();
}

bool get_b_coords(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D point , Vec3D* output)
{
    double area_total = get_tri_area(v1 , v2 , v3);
    double area1 = get_tri_area(v2 , point , v3);
    double area2 = get_tri_area(v3 , point , v1);
    double area3 = get_tri_area(v1 , point , v2);

    output->x = area1 / area_total;
    output->y = area2 / area_total;
    output->z = area3 / area_total;

    // a little bit of tolerance needs to be allowed because floating point operations are not perfectly accurate.
    if (output->x + output->y + output->z < 1.01 && output->x + output->y + output->z > 0.99) {
        return true;
    } else {
        return false;
    }
}
