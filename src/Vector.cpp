#include "Vector.h"

// quake's fast inverse square root algorithm
float fastInverseSquareRoot(float number)
{
	const float threehalfs = 1.5F;

	float x2 = number * 0.5F;
	float y = number;

	// evil floating point bit level hacking
	long i = *(long*)&y;

	// value is pre-assumed
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;

	// 1st iteration
	y = y * (threehalfs - (x2 * y * y));

	return y;
}

Vector2d::Vector2d()
{
	this->x = 0;
	this->y = 0;
}

Vector2d::Vector2d(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector2d operator+(const Vector2d& v, const Vector2d& u)
{
	return Vector2d(v.x + u.x, v.y + u.y);
}

Vector2d operator-(const Vector2d& v, const Vector2d& u)
{
	return Vector2d(v.x - u.x, v.y - u.y);
}

Vector2d operator*(const Vector2d& v, const Vector2d& u)
{
	return Vector2d(v.x * u.x, v.y * u.y);
}

Vector2d operator/(const Vector2d& v, const Vector2d& u)
{
	return Vector2d(v.x / u.x, v.y / u.y);
}

Vector2d operator*(Vector2d v, const double& x)
{
	return Vector2d(v.x * x, v.y * x);
}

Vector2d operator*(const double& x, Vector2d v)
{
	return Vector2d(v.x * x, v.y * x);
}

Vector2d operator/(Vector2d v, const double& x)
{
	return Vector2d(v.x / x, v.y / x);
}

std::ostream& operator<<(std::ostream& stream, const Vector2d& v)
{
	return stream << "[" << v.x << ", " << v.y << "]";
}

Vector2d& Vector2d::operator+=(const Vector2d& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2d& Vector2d::operator*=(const Vector2d& v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Vector2d& Vector2d::operator/=(const Vector2d& v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

Vector2d& Vector2d::operator*=(const double& x)
{
	this->x *= x;
	this->y *= x;
	return *this;
}

Vector2d& Vector2d::operator/=(const double& x)
{
	this->x /= x;
	this->y /= x;
	return *this;
}

double Vector2d::length()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2d Vector2d::normal()
{
	double lenght = this->length();
	return Vector2d(this->x / lenght, this->y / lenght);
}

Vector2d Vector2d::fastNormal()
{
	float invsqrt = fastInverseSquareRoot(this->x * this->x + this->y * this->y);
	return Vector2d(this->x * invsqrt, this->y * invsqrt);
}