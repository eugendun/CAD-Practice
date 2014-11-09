#include "Vec4.h"
#include "Matrix4.h"

class IDrawable
{
public:
	virtual ~IDrawable() {};

	virtual void draw() = 0;
};