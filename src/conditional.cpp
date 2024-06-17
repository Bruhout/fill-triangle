#include "../include/vec3d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>

class Line
{
public:
	float a;
	float b;
	float c;
	bool shaded_side; // if this is true, means the upper shaded_side is shaded

	Line(float x1 , float y1 , float x2 , float y2 , float point_x , float point_y)
	{
		a = y1 - y2;
		b = x2 - x1;
		c = y2*x1 - y1*x2;

		if (a*point_x + b*point_y + c > 0) {
			shaded_side = true;
		} else {
			shaded_side = false;
		}
	}

	// check if a given point lines within the shaded region of the line
	bool point_check(float x1 , float y1)
	{
		if (shaded_side == true)
		{
			if (a*x1 + b*y1 + c > 0) {
				return true;
			} else {
				return false;
			}
		}
		else
		{
			if (a*x1 + b*y1 + c < 0) {
				return true;
			} else {
				return false;
			}
		}
	}

};

int main(void)
{
	unsigned int width = 1024;
	unsigned int height = 1024;
	unsigned int bytes_per_pixel = 3;
	unsigned int image_size = width * height * bytes_per_pixel;

	unsigned char* image_data = (unsigned char*)malloc(image_size);

	Vec3D v1(0.5f , 0.2f , 0.0f);
	Vec3D v2(0.7f , 0.5f , 0.0f);
	Vec3D v3(0.3f , 0.8f , 0.0f);

	Line line1(v1.x , v1.y , v2.x , v2.y , v3.x , v3.y);
	Line line2(v2.x , v2.y , v3.x , v3.y , v1.x , v1.y);
	Line line3(v3.x , v3.y , v1.x , v1.y , v2.x , v2.y);

	for (int i=0 ; i<height ; i++)
	{
		for (int j=0 ; j<width ; j++)
		{
			if (
				line1.point_check(j/(float)width , i/(float)height) &&
				line2.point_check(j/(float)width , i/(float)height) &&
				line3.point_check(j/(float)width , i/(float)height)
			)
			{
				*(image_data + (i*width+j)*3 + 0) = 200;
				*(image_data + (i*width+j)*3 + 1) = 200;
				*(image_data + (i*width+j)*3 + 2) = 200;
			}
			else
			{
				*(image_data + (i*width+j)*3 + 0) = 50;
				*(image_data + (i*width+j)*3 + 1) = 50;
				*(image_data + (i*width+j)*3 + 2) = 50;
			}
		}
	}

	stbi_write_jpg("conditional.jpg" , width , height , bytes_per_pixel , image_data , 100);
	free(image_data);
}
