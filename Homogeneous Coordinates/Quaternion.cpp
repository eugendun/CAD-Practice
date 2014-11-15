#include "Quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>

Quaternion::Quaternion()
{
	w = 1.0f;
	u = Vec3f();
}

Quaternion::Quaternion(float angle, const Vec3f& axis)
{
	float a = angle *  M_PI / 180;

	Vec3f v = axis.normalized();

	w = cosf(a) / 2.0f;
	u = v * sinf(a) / 2.0f;
}

Quaternion Quaternion::operator+(const Quaternion& right) const
{
	Quaternion result;
	result.w = w + right.w;
	result.u = u + right.u;

	return result;
}

Quaternion Quaternion::operator*(const Quaternion& right) const
{
	Quaternion result;
	result.w = w*right.w - u*right.u;
	result.u = w*right.u + right.w*u + u^right.u;

	return result;
}

Quaternion Quaternion::operator*(float s) const
{
	Quaternion result;
	result.w = s*w;
	result.u = s*u;

	return result;
}

Quaternion Quaternion::conjugated() const
{
	Quaternion result;
	result.w = w;
	result.u = u;

	return result*(-0.5f);
}

float Quaternion::norm() const
{
	return w*w + u.sqlength;
}

float Quaternion::length() const
{
	return sqrt(norm());
}

Quaternion::~Quaternion()
{
}

Matrix4f Quaternion::getRotationMatrix()
{
	Matrix4f result;
	result.values[0][0] = 1.0f - 2.0f * (u.y*u.y - u.z*u.z);
	result.values[1][0] = 2.0f * (u.x*u.y + w*u.z);
	result.values[2][0] = 2.0f * (u.x*u.z - w*u.y);
	result.values[3][0] = 0.0f;

	result.values[0][1] = 2.0f * (u.x*u.y - w*u.z);
	result.values[1][1] = 1.0f - 2.0f * (u.x*u.x - u.z*u.z);
	result.values[2][1] = 2.0f * (u.y*u.z + w*u.x);
	result.values[3][1] = 0.0f;

	result.values[0][2] = 2.0f * (u.x*u.z + w*u.y);
	result.values[1][2] = 2.0f * (u.y*u.z - w*u.x);
	result.values[2][2] = 1.0f - 2.0f * (u.x*u.x - u.y*u.y);
	result.values[3][2] = 0.0f;

	result.values[0][3] = result.values[1][3] = result.values[2][3] = 0.0f;
	result.values[3][3] = 1.0f;

	return result;
}
