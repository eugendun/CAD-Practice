#include "NURBS_Surface.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

NURBS_Surface::NURBS_Surface()
{
	// test surface
	std::vector<Vec4f> pRow1;
	pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f) * 2.0f);
	controlPoints.push_back(pRow1);

	std::vector<Vec4f> pRow2;
	pRow2.push_back(Vec4f(0.0f, 2.0f, -1.0f, 1.0f));
	pRow2.push_back(Vec4f(2.0f, 2.0f, -1.0f, 1.0f) * 6.0f);
	pRow2.push_back(Vec4f(2.0f, 0.0f, -1.0f, 1.0f) * 2.0f);
	controlPoints.push_back(pRow2);

	std::vector<Vec4f> pRow3;
	pRow3.push_back(Vec4f(0.0f, 1.0f, -2.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, 1.0f, -2.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, 0.0f, -2.0f, 1.0f) * 2.0f);
	controlPoints.push_back(pRow3);

	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(1.0f);
	knotVectorU.push_back(1.0f);
	knotVectorU.push_back(1.0f);

	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(1.0f);
	knotVectorV.push_back(1.0f);
	knotVectorV.push_back(1.0f);

	degree = 2;

	isValidNURBS();
}

NURBS_Surface::NURBS_Surface(const std::vector<std::vector<Vec4f>>& controlPoints_, const std::vector<float>& knotVectorU_, const std::vector<float>& knotVectorV_, const unsigned int degree_)
	: controlPoints(controlPoints_)
	, knotVectorU(knotVectorU_)
	, knotVectorV(knotVectorV_)
	, degree(degree_)
{
	isValidNURBS();
}

bool NURBS_Surface::isValidNURBS()
{
	// knot vector U verification
	bool validU = true;
	for (unsigned int i = 1; i < knotVectorU.size() && validU == true; ++i)
	{
		if (knotVectorU[i] < knotVectorU[i-1])
		{
			std::cout << "INVALID (unsorted) knotVectorU.\n";
			validU = false;
			break;
		}
	}
	// knot vector V verification
	bool validV = true;
	for (unsigned int i = 1; i < knotVectorV.size() && validV == true; ++i)
	{
		if (knotVectorV[i] < knotVectorV[i-1])
		{
			std::cout << "INVALID (unsorted) knotVectorV.\n";
			validV = false;
			break;
		}
	}
	// size verification
	bool validSize = true;
	for (unsigned int i = 1; i < controlPoints.size() && validSize == true; ++i)
	{
		if (controlPoints[i].size() != controlPoints[i-1].size())
		{
			std::cout << "INVALID mesh (Each row has to have the same number of control points).\n";
			validSize = false;
		}
	}
	if (controlPoints[0].size() + degree + 1 != knotVectorU.size()) 
	{
		std::cout << "INVALID size in u direction (controlPoints[0].size() + degree + 1 != knotVectorU.size()).\n";
		validSize = false;
	}
	if (controlPoints.size() + degree + 1 != knotVectorV.size()) 
	{
		std::cout << "INVALID size in v direction (controlPoints.size() + degree + 1 != knotVectorV.size()).\n";
		validSize = false;
	}
	return (validU && validV && validSize);
}

Vec4f NURBS_Surface::evaluteDeBoor(const float u, const float v, Vec4f& tangentU, Vec4f& tangentV)
{
	Vec4f evaluatedPoint;
	// TODO: evaluate the surface by evaluating curves
	// ===============================================
	std::vector<Vec4f> temp;
	temp.reserve(controlPoints.size());
	for (int i = 0; i < controlPoints.size(); i++)
	{
		NURBS_Curve nurbsCurve = NURBS_Curve(controlPoints[i], knotVectorU, degree);
		temp.push_back(nurbsCurve.evaluteDeBoor(u, tangentU));
	}

	NURBS_Curve nurbsCurve = NURBS_Curve(temp, knotVectorV, degree);
	evaluatedPoint = nurbsCurve.evaluteDeBoor(v, tangentV);
	// ===============================================
	return evaluatedPoint;
}

std::ostream& operator<< (std::ostream& os, NURBS_Surface& nurbsSurface)
{
	// degree
	os << "NURBS surface, degree " << nurbsSurface.degree << "\n";
	// control points
	os << "  " << nurbsSurface.controlPoints.size() << " x " << nurbsSurface.controlPoints[0].size() << " controlPoints:\n";
	for (unsigned int i = 0; i < nurbsSurface.controlPoints.size(); ++i)
		for (unsigned int j = 0; j < nurbsSurface.controlPoints[i].size(); ++j)
			os << "    " << nurbsSurface.controlPoints[i][j] << "\n";
	// knot vector U 
	os << "  " << nurbsSurface.knotVectorU.size() << " knotVectorU: ";
	for (unsigned int i = 0; i < nurbsSurface.knotVectorU.size(); ++i) os << nurbsSurface.knotVectorU[i] << ", ";
	os << "\n";
	// knot vector V 
	os << "  " << nurbsSurface.knotVectorV.size() << " knotVectorV: ";
	for (unsigned int i = 0; i < nurbsSurface.knotVectorU.size(); ++i) os << nurbsSurface.knotVectorV[i] << ", ";
	os << "\n";
	// knot vector verification
	nurbsSurface.isValidNURBS();
	return os;
}