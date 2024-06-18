#include <iostream>
#include <math.h>

#include "../include/bounding_box.h"
#include "../include/vec3d.h"

void get_bounding_box(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D* top_left , Vec3D* bottom_right)
{
	top_left->x = std::min(v1.x , std::min(v2.x , v3.x));
	top_left->y = std::min(v1.y , std::min(v2.y , v3.y));

	bottom_right->x = std::max(v1.x , std::max(v2.x , v3.x));
	bottom_right->y = std::max(v1.y , std::max(v2.y , v3.y));
}
