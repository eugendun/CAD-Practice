#pragma once

#include "IDrawable.h"
#include "Transform.h"
#include "Vec3.h"

#include <GL/glut.h>

class Point : public IDrawable, public Transform
{
public:
	Point();
	~Point();

	void draw();
};