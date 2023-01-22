#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

struct Vector2d
{
	double x, y;

	Vector2d();
	Vector2d(double x, double y);

	friend Vector2d operator+(const Vector2d& v, const Vector2d& u);
	friend Vector2d operator-(const Vector2d& v, const Vector2d& u);
	friend Vector2d operator*(const Vector2d& v, const Vector2d& u);
	friend Vector2d operator/(const Vector2d& v, const Vector2d& u);

	friend Vector2d operator*(Vector2d v, const double& x);
	friend Vector2d operator*(const double& x, Vector2d v);
	friend Vector2d operator/(Vector2d v, const double& x);

	Vector2d& operator+=(const Vector2d& v);
	Vector2d& operator-=(const Vector2d& v);
	Vector2d& operator*=(const Vector2d& v);
	Vector2d& operator/=(const Vector2d& v);

	Vector2d& operator*=(const double& x);
	Vector2d& operator/=(const double& x);

	double length();
	Vector2d normal();
	Vector2d fastNormal();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2d& v);
};

#endif