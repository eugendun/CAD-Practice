#pragma once

#include "Vec4.h"

#include <vector>

class CurveGenerator
{
public:
	CurveGenerator();
	virtual ~CurveGenerator();

	static Vec4d deCasteljau(std::vector<Vec4d> P, double u);
	static std::vector<Vec4d> diffCurve(std::vector<Vec4d> & P);

	static std::vector<Vec4d> bezierCurve(int m, std::vector<Vec4d> P, int n);
	static std::vector<Vec4d> bezierRationalCurve(int m, std::vector<Vec4d> P, int n);
};

