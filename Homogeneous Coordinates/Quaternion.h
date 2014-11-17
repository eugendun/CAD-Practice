#pragma once

class Quaternion;

#include "Vec4.h"
#include "Matrix4.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float angle, const Vec3f& axis);

	~Quaternion();

	Quaternion operator+ (const Quaternion& right) const;
	Quaternion operator* (float s) const;
	Quaternion operator* (const Quaternion& right) const;

	Quaternion conjugated() const;
	float norm() const;
	float length() const;

	Matrix4f getRotationMatrix();

	float getAngle() const;
	const Vec3f& getAxis() const;

private:
	float w;
	Vec3f u;
};

