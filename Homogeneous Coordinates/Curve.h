#pragma once

#include "Vec3.h"
#include "Vec4.h"

#include <vector>

class Curve
{
public:
	Curve();
	virtual ~Curve();

	void addPoint(Vec4d point);
	void draw();

	void controlCurveEnabled(bool enabled);
	void controlPointsEnabeld(bool enabled);
	void derivationEnabled(bool enabled);
	void bezierEnabled(bool enabled);
	void setLineSegments(int m);
	int getNearesControlPoint(Vec3d point);
	void removeSelection();
	void moveControlPoint(int index, Vec3d newPos);
	void increaseWeightOfPoint(int index);
	void decreaseWeightOfPoint(int index);

	bool bControlCurve, bControlPoints, bBezier, bDerivation, bRational;
private:
	std::vector<Vec4d> points;
	std::vector<Vec4d> bezier;
	std::vector<Vec4d> rational;
	std::vector<Vec4d> bezierDerivation;

	int lineSegments, selectedPointIndex;

	void recalcBezier();
	void recalcBezierDerivation();
	void recalcRational();

	void drawControlCurve();
	void drawControlPoints();
	void drawDerivation();
	void drawBezier();
	void drawRational();
};

