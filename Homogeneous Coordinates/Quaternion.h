#pragma once

class Quaternion;

#include "Vec4.h"
#include "Matrix4.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float w, const Vec3f& u);
	Quaternion(float w, float x, float y, float z);

	~Quaternion();

	static Quaternion rotationQuaternion(float angle, const Vec3f& axis);

	Quaternion operator+ (const Quaternion& right) const;
	Quaternion operator* (float s) const;
	Quaternion operator* (const Quaternion& right) const;

	Quaternion conjugated() const;
	Quaternion normalized() const;
	float norm() const;
	float length() const;

	Matrix4f getRotationMatrix();

	float getAngle() const;
	const Vec3f& getAxis() const;

	float w;
	Vec3f u;
};

