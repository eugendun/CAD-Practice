#include "CurveGenerator.h"

CurveGenerator::CurveGenerator()
{
}


CurveGenerator::~CurveGenerator()
{
}

Vec3d CurveGenerator::deCasteljau(std::vector<Vec3d> P, double u)
{
	std::vector<Vec3d> Q = P;

	for (int k = 0; k < P.size(); k++)
	{
		for (int i = 0; i < P.size() - k - 1; i++)
		{
			Q[i] = (1.0 - u) * Q[i] + u * Q[i + 1];
		}
	}

	return Q[0];
}

std::vector<Vec3d> CurveGenerator::diffCurve(std::vector<Vec3d> & P)
{
	std::vector<Vec3d> Q;

	if (P.size() == 1)
	{
		Q = std::vector<Vec3d>(1);
		Q[0] = P[0];
		return Q;
	}

	Q = std::vector<Vec3d>(P.size());

	for (int i = 0; i < P.size() - 1; i++)
	{
		Q[i] = P[i + 1] - P[i];
	}

	return Q;
}

std::vector<Vec3d> CurveGenerator::bezierCurve(int m, std::vector<Vec3d> P, int n)
{
	std::vector<Vec3d> C(P.size());

	for (int i = 0; i < m; i++)
	{
		C.push_back(deCasteljau(P, i / (double)m));
	}

	return C;
}

std::vector<Vec3d> CurveGenerator::bezierRationalCurve(int m, std::vector<Vec3d> P, int n)
{
	for (int i = 0; i < n; i++)
	{
		P[i].x = P[i].x / P[i].z;
		P[i].y = P[i].y / P[i].z;
		P[i].z = P[i].z / P[i].z;
	}

	return bezierCurve(m, P, n);
}