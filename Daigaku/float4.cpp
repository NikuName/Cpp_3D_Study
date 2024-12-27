#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>
#include <Eigen/Dense>
#include "Header.h"

using namespace std;


float4::float4() : x(0), y(0), z(0), w(0)
{

}
float4::float4(float x) : x(x), y(0), z(0), w(0)
{

}
float4::float4(float x, float y) : x(x), y(y), z(0), w(0)
{

}
float4::float4(float x, float y, float z) : x(x), y(y), z(z), w(0)
{

}
float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}
float4::float4(const float4& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
}
float4& float4::operator=(const float4* vector)
{
	x = vector->x;
	y = vector->y;
	z = vector->z;
	w = vector->w;
	return *this;
}
float4& float4::operator=(const float4& vect2)
{
	x = vect2.x;
	y = vect2.y;
	z = vect2.z;
	w = vect2.w;
	return *this;
}
float4& float4::operator*(const float& value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}
float4& float4::operator/(const float& value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
	return *this;
}
float4& float4::operator+(const float4& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}
float4& float4::operator-(const float4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}
float& float4::operator[](int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return x;
	}
}
float float4::Dot(float4 v1, float4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
float4 float4::Cross(float4 v1, float4 v2)
{
	return { v1.y * v2.z - v1.z * v2.y, -(v1.x * v2.z - v1.z * v2.x), v1.x * v2.y - v1.y * v2.x };
}
float float4::sqrtDistance()
{
	return x * x + y * y + z * z;
}
float float4::distance()
{
	return sqrtf(x * x + y * y + z * z);
}
void float4::ToString()
{
	cout << x << ", " << y << ", " << z << ", " << w << '\n';
}
VectorXd float4::getVector()
{
	VectorXd v = VectorXd(4);
	v(0) = x;
	v(1) = y;
	v(2) = z;
	v(3) = w;
	return v;
}
void float4::setVector(const VectorXd& v)
{
	x = v(0);
	y = v(1);
	z = v(2);
	w = v(3);
}
VectorXd float4::V2V(float4 v)
{
	VectorXd v2 = VectorXd(4);
	v2(0) = v.x;
	v2(1) = v.y;
	v2(2) = v.z;
	v2(3) = v.w;
	return v2;
}
float4 float4::V2V(VectorXd v)
{
	return { (float)v(0), (float)v(1), (float)v(2), (float)v(3) };
}
float4 float4::normalized()
{
	return float4{ x, y, z, w } / distance();
}
float4::~float4()
{

}
