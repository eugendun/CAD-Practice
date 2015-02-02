#include "Curve.h"
#include "CurveGenerator.h"

#include <GL/glut.h>
#include <limits>

#include <stdio.h>		// cout
#include <iostream>		// cout

Curve::Curve()
{
	bControlCurve = true;
	bControlPoints = true;
	bDerivation = false;
	bBezier = false;
	bRational = true;
	lineSegments = 20;
	selectedPointIndex = -1;
}


Curve::~Curve()
{
}

void Curve::addPoint(Vec4d point)
{
	points.push_back(point);

	recalcBezier();
	recalcBezierDerivation();
	recalcRational();
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

	if (bRational)
	{
		drawRational();
	}
}

void Curve::drawRational()
{
	glBegin(GL_LINES);
	glColor3f(.5f, 0.0f, 0.0f);
	for (int i = 0; i < rational.size() - 1; i++)
	{
		double w = rational[i].w;
		double w_2 = rational[i + 1].w;

		glVertex3f(rational[i].x/w, rational[i].y/w, rational[i].z/w);
		glVertex3f(rational[i + 1].x/w_2, rational[i + 1].y/w_2, rational[i + 1].z/w_2);
	}
	glEnd();
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
	for (int i = 0; i < points.size(); i++)
	{
		if (i == selectedPointIndex)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
		}
		else{
			glColor3f(0.0f, 0.0f, 1.0f);
		}
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}

void Curve::recalcBezier()
{
	bezier = CurveGenerator::bezierCurve(lineSegments, points, points.size());
}

void Curve::recalcBezierDerivation()
{
	std::vector<Vec4d> diffs = CurveGenerator::diffCurve(points);
	bezierDerivation = CurveGenerator::bezierCurve(lineSegments, diffs, diffs.size());
	for (int i = 0; i < bezierDerivation.size(); i++)
	{
		bezierDerivation[i] = (double)points.size() * bezierDerivation[i];
	}
}

void Curve::recalcRational()
{
	std::vector<Vec4d> temp = std::vector<Vec4d>();

	for (int i = 0; i < points.size(); i++)
	{
		temp.push_back(Vec4d(points[i].w*points[i].x, points[i].w*points[i].y, points[i].w*points[i].z, points[i].w));
	}

	rational = CurveGenerator::bezierCurve(lineSegments, temp, temp.size());
}

void Curve::setLineSegments(int m)
{
	lineSegments = m;
	recalcBezier();
}

int Curve::getNearesControlPoint(Vec3d point)
{
	int index = -1;
	double minDistance = 0.01;
	for (int i = 0; i < points.size(); i++)
	{
		double sqDistance = (point.x - points[i].x) * (point.x - points[i].x)
			+ (point.y - points[i].y) * (point.y - points[i].y)
			+ (point.z - points[i].z) * (point.z - points[i].z);

		if (sqDistance < minDistance)
		{
			minDistance = sqDistance;
			index = i;
		}
	}

	selectedPointIndex = index;

	std::cout << minDistance << std::endl;

	return selectedPointIndex;
}

void Curve::removeSelection()
{
	selectedPointIndex = -1;
}

void Curve::moveControlPoint(int index, Vec3d newPos)
{
	if (index > -1 && index < points.size())
	{
		points[index].x = newPos.x;
		points[index].y = newPos.y;
		//points[index].z = newPos.z;
	}

	recalcBezier();
	recalcBezierDerivation();
	recalcRational();
}

void Curve::increaseWeightOfPoint(int index)
{
	if (index > -1 && index < points.size())
	{
		points[index].w += 0.1;
		recalcBezier();
		recalcBezierDerivation();
		recalcRational();
		std::cout << "P[" << index << "].w=" << points[index].w << std::endl;
	}
}

void Curve::decreaseWeightOfPoint(int index)
{
	if (index > -1 && index < points.size())
	{
		points[index].w -= 0.1;
		recalcBezier();
		recalcBezierDerivation();
		recalcRational();
		std::cout << "P[" << index << "].w=" << points[index].w << std::endl;
	}
}