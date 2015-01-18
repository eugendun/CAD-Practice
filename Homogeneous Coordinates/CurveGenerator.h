#pragma once

#include "Vec3.h"

#include <vector>

class CurveGenerator
{
public:
	CurveGenerator();
	virtual ~CurveGenerator();

	static Vec3d deCasteljau(std::vector<Vec3d> P, double u);
	static std::vector<Vec3d> diffCurve(std::vector<Vec3d> & P);

	static std::vector<Vec3d> bezierCurve(int m, std::vector<Vec3d> P, int n);
	static std::vector<Vec3d> bezierRationalCurve(int m, std::vector<Vec3d> P, int n);
};

