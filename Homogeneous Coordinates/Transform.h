#pragma once

#include "Vec4.h"
#include "Matrix4.h"

class Transform
{
public:
	Transform();
	virtual ~Transform();

	void setPosition(const Vec4f& p);
	void setOrientation(const Matrix4f& m);

	const Vec4f& getPosition() const;
	const Matrix4f& getOrientation() const;

protected:
	Vec4f position;
	Matrix4f orientation;
};