#include "../include/vec3d.h"
#include <math.h>
#include <iostream>

Vec3D::Vec3D()
    : x(0),
      y(0),
      z(0) 
{}

Vec3D::Vec3D(double X , double Y , double Z)
    : x(X),
      y(Y),
      z(Z) 
{}

Vec3D Vec3D::operator-(Vec3D vec2)
{
    Vec3D subVec = {
        x - vec2.x,
        y - vec2.y,
        z - vec2.z
    };

    return subVec;
}

Vec3D Vec3D::operator+(Vec3D vec2)
{
    Vec3D subVec = {
        x + vec2.x,
        y + vec2.y,
        z + vec2.z
    };

    return subVec;
}

Vec3D Vec3D::operator*(double scalar)
{
    Vec3D subVec = {
        x * scalar,
        y * scalar,
        z * scalar
    };

    return subVec;
}

Vec3D Vec3D::operator/(double scalar)
{
    Vec3D subVec = {
        x / scalar,
        y / scalar,
        z / scalar
    };

    return subVec;
}


double Vec3D::MagnitudeSq()
{
    return pow(x, 2) + pow(y , 2) + pow(z, 2);
}

double Vec3D::Magnitude()
{
    return pow(MagnitudeSq() , 0.5);
}

double Vec3D::DistanceFrom(Vec3D refPoint)
{
    return ((refPoint - *this).Magnitude());
}

Vec3D Vec3D::CrossProduct(Vec3D vec2)
{
    Vec3D productVec = {
        ((y * vec2.z) - (z * vec2.y)),
        -((x * vec2.z) - (z * vec2.x)),
        ((x * vec2.y) - (y * vec2.x))
    };
    return productVec;
}

double Vec3D::DotProduct(Vec3D vec2)
{
    return (x * vec2.x) + (y * vec2.y) + (z * vec2.z);
}

Vec3D Vec3D::GetUnitVec()
{
    Vec3D origin = {0,0,0};
    double mag = DistanceFrom(origin);
    Vec3D unitVec = {
        x / mag,
        y / mag,
        z / mag
    };

    return unitVec;
}

Vec3D Vec3D::ProjectOnto(Vec3D ontoVec)
{
    double scaleFactor = DotProduct(ontoVec) / ontoVec.Magnitude();

    Vec3D projVec = ontoVec.GetUnitVec() * scaleFactor;

    return projVec;
}

void Vec3D::PrintVec()
{
    std::clog << "(" << x << ',' << y << ',' << z << ")\n";
}

Vec3D Vec3D::Normalize(int width , int height)
{
    return Vec3D(
        x / width,
        y / height,
        z
    );
}
