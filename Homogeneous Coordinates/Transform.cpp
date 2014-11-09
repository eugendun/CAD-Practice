#include "Transform.h"


Transform::Transform()
{
}


Transform::~Transform()
{
}

void Transform::setPosition(const Vec4f& p) {
	position = Vec4f(p);
}

void Transform::setOrientation(const Matrix4f& m){
	orientation = Matrix4f(m);
}

const Vec4f& Transform::getPosition() const {
	return position;
}

const Matrix4f& Transform::getOrientation() const {
	return orientation;
}
