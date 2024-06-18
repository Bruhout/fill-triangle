#include "../include/vec3d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <chrono>

class Line
{
public:
	float a;
	float b;
	float c;
	bool shaded_side; // if this is true, means the upper shaded_side is shaded

	Line(Vec3D p1 , Vec3D p2 , Vec3D check_point)
		: a(p1.y - p2.y),
		  b(p2.x - p1.x),
		  c(p2.y*p1.x - p1.y*p2.x)
	{
		if (a*check_point.x + b*check_point.y + c > 0) {
			shaded_side = true;
		} else {
			shaded_side = false;
		}
	}

	// check if a given point lines within the shaded region of the line
	bool point_check(Vec3D point)
	{
		if (shaded_side == true)
		{
			if (a*point.x + b*point.y + c > 0) {
				return true;
			} else {
				return false;
			}
		}
		else
		{
			if (a*point.x + b*point.y + c < 0) {
				return true;
			} else {
				return false;
			}
		}
	}

};

int main(void)
{
	unsigned int width = 512;
	unsigned int height = 512;
	unsigned int bytes_per_pixel = 3;
	unsigned int image_size = width * height * bytes_per_pixel;

	unsigned char* image_data = (unsigned char*)malloc(image_size);

	Vec3D v1(0.5f , 0.2f , 0.0f);
	Vec3D v2(0.7f , 0.5f , 0.0f);
	Vec3D v3(0.3f , 0.8f , 0.0f);

	Line line1(v1 , v2 , v3);
	Line line2(v2 , v3 , v1);
	Line line3(v3 , v1 , v2);
	
	// START CLOCK
	std::chrono::_V2::system_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	for (int i=0 ; i<height ; i++)
	{
		for (int j=0 ; j<width ; j++)
		{
			if (
				line1.point_check(Vec3D(j/(float)width , i/(float)height , 0)) &&
				line2.point_check(Vec3D(j/(float)width , i/(float)height , 0)) &&
				line3.point_check(Vec3D(j/(float)width , i/(float)height , 0))
			)
			{
				*(image_data + (i*width+j)*3 + 0) = 200;
				*(image_data + (i*width+j)*3 + 1) = 50;
				*(image_data + (i*width+j)*3 + 2) = 50;
			}
			else
			{
				*(image_data + (i*width+j)*3 + 0) = 0;
				*(image_data + (i*width+j)*3 + 1) = 120;
				*(image_data + (i*width+j)*3 + 2) = 120;
			}
		}
	}

	// CALCULATE TIME TAKEN FOR EXECUTION AND PRINT IT OUT
	std::chrono::_V2::system_clock::time_point stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time); 
	std::cout << "Time taken by conditional was: " << duration.count() << " microseconds" << '\n';

	stbi_write_jpg("conditional.jpg" , width , height , bytes_per_pixel , image_data , 100);
	free(image_data);
}
