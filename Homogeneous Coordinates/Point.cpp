#include "Point.h"

Point::Point()
{

}

Point::~Point()
{
}

void Point::draw() {
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	// draw point in the current origin position
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	
	glPopMatrix();
}