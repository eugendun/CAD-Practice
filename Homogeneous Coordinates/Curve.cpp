#include "Curve.h"
#include "CurveGenerator.h"

#include <GL/glut.h>

Curve::Curve()
{
	bControlCurve = true;
	bControlPoints = true;
	bDerivation = true;
	bBezier = true;
	lineSegments = 10;
}


Curve::~Curve()
{
}

void Curve::addPoint(Vec3d point)
{
	points.push_back(point);

	recalcBezier();
	recalcBezierDerivation();
}

void Curve::draw()
{
	if (bControlCurve)
	{
		drawControlCurve();
	}

	if (bBezier)
	{
		drawBezier();
	}

	if (bDerivation)
	{
		drawDerivation();
	}
}

void Curve::drawBezier()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < bezier.size() - 1; i++)
	{
		glVertex3f(bezier[i].x, bezier[i].y, bezier[i].z);
		glVertex3f(bezier[i + 1].x, bezier[i + 1].y, bezier[i + 1].z);
	}
	glEnd();
}

void Curve::drawDerivation()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < bezierDerivation.size() - 1; i++)
	{
		glVertex3f(bezierDerivation[i].x, bezierDerivation[i].y, bezierDerivation[i].z);
		glVertex3f(bezierDerivation[i + 1].x, bezierDerivation[i + 1].y, bezierDerivation[i + 1].z);
	}
	glEnd();
}

void Curve::drawControlCurve()
{
	if (bControlPoints)
	{
		drawControlPoints();
	}

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = 0; i < points.size() - 1; i++)
	{
		glVertex3f(points[i].x, points[i].y, points[i].z);
		glVertex3f(points[i + 1].x, points[i + 1].y, points[i + 1].z);
	}
	glEnd();
}

void Curve::drawControlPoints()
{
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 1.0f);
	for each (Vec3d p in points)
	{
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();
}

void Curve::recalcBezier()
{
	bezier = CurveGenerator::bezierCurve(lineSegments, points, points.size());
}

void Curve::recalcBezierDerivation()
{
	std::vector<Vec3d> diffs = CurveGenerator::diffCurve(points);
	bezierDerivation = CurveGenerator::bezierCurve(lineSegments, diffs, diffs.size());
	for (int i = 0; i < bezierDerivation.size(); i++)
	{
		bezierDerivation[i] = (double)points.size() * bezierDerivation[i];
	}
}

void Curve::controlCurveEnabled(bool enabled)
{
	bControlCurve = enabled;
}

void Curve::controlPointsEnabeld(bool enabled)
{
	bControlPoints = enabled;
}

void Curve::derivationEnabled(bool enabled)
{
	bDerivation = enabled;
}

void Curve::bezierEnabled(bool enabled)
{
	bBezier = enabled;
}

void Curve::setLineSegments(int m)
{
	lineSegments = m;
	recalcBezier();
}