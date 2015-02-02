#include "NURBS_Curve.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

NURBS_Curve::NURBS_Curve()
{
	controlPoints.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f) * 1.0f);
	controlPoints.push_back(Vec4f(1.0f, 1.0f, 0.0f, 1.0f) * 1.0f);
	controlPoints.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f) * 2.0f);
	knotVector.push_back(0.0f);
	knotVector.push_back(0.0f);
	knotVector.push_back(0.0f);
	knotVector.push_back(1.0f);
	knotVector.push_back(1.0f);
	knotVector.push_back(1.0f);
	degree = 2;
	isValidNURBS();
}

// constructor which takes given control points P, knot vector U and degree p
NURBS_Curve::NURBS_Curve(const std::vector<Vec4f>& controlPoints_, const std::vector<float>& knotVector_, const unsigned int degree_)
	: controlPoints(controlPoints_)
	, knotVector(knotVector_)
	, degree(degree_)
{
	isValidNURBS();
}

bool NURBS_Curve::isValidNURBS()
{
	// knot vector verification
	bool validU = true;
	for (unsigned int i = 1; i < knotVector.size() && validU == true; i++) if (knotVector[i] < knotVector[i-1])
	{
		std::cout << "INVALID (unsorted) knotVector.\n";
		validU = false;
		break;
	}
	// size verification
	bool validSize = true;
	if (controlPoints.size() + degree + 1 != knotVector.size()) 
	{
		std::cout << "INVALID sizes (controlPoints.size() + degree + 1 != knotVector.size()).\n";
		validSize = false;
	}
	return (validU && validSize);
}


bool NURBS_Curve::insertKnot(const float newKnot)
{
	// get index k for inserting newKnot
	int k = getIndex(newKnot);
	if (k == -1) return false;
	// create new control points Q and reserve memory for 1 more control point
	std::vector<Vec4f> Q;
	Q.reserve(controlPoints.size() + 1);
	// copy control points up to index k
	for (unsigned int i = 0; i <= k - degree; i++) Q.push_back(controlPoints[i]);
	// calculate new control points
	for (int i = k - degree + 1; i <= k; i++)
	{
		float alpha = (newKnot - knotVector[i]) / (knotVector[i+degree] - knotVector[i]);
		Q.push_back(alpha*controlPoints[i] + (1.0f - alpha) * controlPoints[i-1]);
	}
	// copy remaining control points
	for (unsigned int i = k + 1; i <= controlPoints.size(); i ++) Q.push_back(controlPoints[i-1]);
	// replace control points with new ones
	controlPoints = Q;
	// insert knot in U
	std::vector<float>::iterator it = knotVector.begin();
	it += k + 1;
	knotVector.insert(it, newKnot);
	return true;
}

Vec4f NURBS_Curve::evaluteDeBoor(const float t, Vec4f& tangent)
{
	// create a copy of this NURBS curve
	NURBS_Curve tempNURBS(*this);
	// determine multiplicity of parameter t in U
	int k;
	unsigned int multiplicity = getMultiplicityAndIndex(t, k);
	if (k == -1) return Vec4f(0.0f, 0.0f, 0.0f, 0.0f);
	// special case: start of the curve
	if (t == knotVector.front()) 
	{
		Vec4f& t1 = controlPoints[0];
		Vec4f& t2 = controlPoints[1];
		tangent = Vec4f(t1.w * t2.x - t2.w * t1.x, t1.w * t2.y - t2.w * t1.y, t1.w * t2.z - t2.w * t1.z, t1.w * t2.w);
		return controlPoints.front();
	}
	// special case: end of the curve
	if (t == knotVector.back()) 
	{
		Vec4f& t1 = controlPoints[controlPoints.size() - 2];
		Vec4f& t2 = controlPoints[controlPoints.size() - 1];
		tangent = Vec4f(t1.w * t2.x - t2.w * t1.x, t1.w * t2.y - t2.w * t1.y, t1.w * t2.z - t2.w * t1.z, t1.w * t2.w);
		return controlPoints.back();
	}
	// insert knot p - multiplicity times
	int iterations =  (int)degree - (int)multiplicity;
	for (int i = 0; i < iterations; i++) 
	{
		tempNURBS.insertKnot(t);
	}
	// extract point from the control points of tempNURBS
	int index = tempNURBS.getIndex(t) - tempNURBS.degree;
	// to extract the tangent, use the adjacent control points. Take care to not use the simple subtraction operation on homogene vectors!
	Vec4f& t1 = tempNURBS.controlPoints[index-1];
	Vec4f& t2 = tempNURBS.controlPoints[index+1];
	tangent = Vec4f(t1.w * t2.x - t2.w * t1.x, t1.w * t2.y - t2.w * t1.y, t1.w * t2.z - t2.w * t1.z, t1.w * t2.w);
	return tempNURBS.controlPoints[index];
}

int NURBS_Curve::getIndex(const float u)
{
	// abort if no knot vector available
	if (knotVector.size() == 0) return -1;
	// abort if u is smaller then first knot entry
	if (u < knotVector.front()) return -1;
	// abort if u is bigger then last knot entry
	if (u > knotVector.back()) return -1;
	// search for first knot entry being bigger then u
	int k = 0;
	while (k < knotVector.size()-1 && knotVector[k+1] <= u) k++;
	// else return valid index for inserting a knot in interval [u_k, u_k+1)
	return (int)k;
}

unsigned int NURBS_Curve::getMultiplicityAndIndex(const float u, int &k)
{
	unsigned int multiplicity = 0;
	k = getIndex(u);	
	if (k == -1) return multiplicity;
	// get number of same knots at index k and before
	int tempK = k;
	while (tempK >= 0 && knotVector[tempK] == u)
	{
		multiplicity++;
		tempK--;
	}
	// get number of same knots after index k
	tempK += multiplicity + 1;
	while (tempK < (int)knotVector.size() && knotVector[tempK] == u)
	{
		multiplicity++;
		tempK++;
	}
	return multiplicity;
}

std::ostream& operator<< (std::ostream& os, NURBS_Curve& nurbs)
{
	// degree
	os << "NURBS curve, degree " << nurbs.degree << "\n";
	// control points
	os << "  " << nurbs.controlPoints.size() << " controlPoints:\n";
	for (unsigned int i = 0; i < nurbs.controlPoints.size(); i++) os << "    " << nurbs.controlPoints[i] << "\n";
	// knot vector
	os << "  " << nurbs.knotVector.size() << " knotVector: ";
	for (unsigned int i = 0; i < nurbs.knotVector.size(); i++) os << nurbs.knotVector[i] << ", ";
	os << "\n";
	// knot vector verification
	nurbs.isValidNURBS();
	return os;
}