#pragma once

#include "Vec3.h"

#include <vector>

class Curve
{
public:
	Curve();
	virtual ~Curve();

	void addPoint(Vec3d point);
	void draw();

	void controlCurveEnabled(bool enabled);
	void controlPointsEnabeld(bool enabled);
	void derivationEnabled(bool enabled);
	void bezierEnabled(bool enabled);
	void setLineSegments(int m);

private:
	std::vector<Vec3d> points;
	std::vector<Vec3d> bezier;
	std::vector<Vec3d> bezierDerivation;

	int lineSegments;			// line segments
	bool bControlCurve, bControlPoints, bBezier, bDerivation;

	void recalcBezier();
	void recalcBezierDerivation();

	void drawControlCurve();
	void drawControlPoints();
	void drawDerivation();
	void drawBezier();
};

