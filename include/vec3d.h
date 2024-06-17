#ifndef VEC3D_HPP
#define VEC3D_HPP
#include <iostream>
#include <math.h>

class Vec3D
{
public:
    double x , y , z;

    Vec3D();

    Vec3D(double X , double Y , double Z); 

    Vec3D operator-(Vec3D vec2);

    Vec3D operator+(Vec3D vec2);

    Vec3D operator*(double scalar);

    Vec3D operator/(double scalar);

    double MagnitudeSq();

    double Magnitude();

    double DistanceFrom(Vec3D refPoint);

    Vec3D CrossProduct(Vec3D vec2);

    double DotProduct(Vec3D vec2);

    Vec3D GetUnitVec();

    Vec3D ProjectOnto(Vec3D ontoVec);

    void PrintVec();

    Vec3D Normalize(int width , int height);
};
#endif // VEC3D_HPP