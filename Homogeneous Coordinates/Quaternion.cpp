#include "Quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>

Quaternion::Quaternion()
{
	w = 1.0f;
	u = Vec3f();
}

Quaternion::Quaternion(float w, const Vec3f& u)
{
	this->w = w;
	this->u = u;
}

Quaternion::Quaternion(float w, float x, float y, float z){
	this->w = w;
	this->u.x = x;
	this->u.y = y;
	this->u.z = z;
}

Quaternion Quaternion::rotationQuaternion(float angle, const Vec3f& axis){
	float a = (angle / 2.0f) *  M_PI / 180;

	Vec3f u = axis.normalized();

	float w = cosf(a);
	u = axis * sin(a);

	return Quaternion(w, u);
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
	result.u = (w*right.u) + (right.w*u) + (u^right.u);

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
	result.u = this->u * -1;

	return result;
}

Quaternion Quaternion::normalized() const
{
	Quaternion result;
	result.w = this->w;
	result.u.x = this->u.x;
	result.u.y = this->u.y;
	result.u.z = this->u.z;

	float l = this->length();

	return result * (1.0f / l);
}

float Quaternion::norm() const
{
	return w*w + u.sqlength();
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
	result.values[0][0] = 1 - 2 * u.y*u.y - 2 * u.z*u.z;
	result.values[1][0] = 2 * u.x*u.y + 2 * w*u.z;
	result.values[2][0] = 2 * u.x*u.z - 2 * w*u.y;
	result.values[3][0] = 0;

	result.values[0][1] = 2 * u.x*u.y - 2 * w*u.z;
	result.values[1][1] = 1 - 2 * u.x*u.x - 2 * u.z*u.z;
	result.values[2][1] = 2 * u.y*u.z + 2 * w*u.x;
	result.values[3][1] = 0;

	result.values[0][2] = 2 * u.x*u.z + 2 * w*u.y;
	result.values[1][2] = 2 * u.y*u.z - 2 * w*u.x;
	result.values[2][2] = 1 - 2 * u.x*u.x - 2 * u.y*u.y;
	result.values[3][2] = 0;

	result.values[0][3] = result.values[1][3] = result.values[2][3] = 0;
	result.values[3][3] = 1;

	return result;
}


float Quaternion::getAngle() const {
	return w;
}


const Vec3f& Quaternion::getAxis() const {
	return u;
}