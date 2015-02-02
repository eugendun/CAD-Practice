#ifndef NURBS_CURVE_H
#define NURBS_CURVE_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>

#include "Vec4.h"		// vector (x, y, z, w)

class NURBS_Curve {

public:

	// class data:
	std::vector<Vec4f> controlPoints;
	std::vector<float> knotVector;
	unsigned int degree;

	// empty constructor which creates a degree 2 quarter circle in first quadrant, XY-plane
	NURBS_Curve();

	// constructor which takes given control points P, knot vector U and degree p
	NURBS_Curve(const std::vector<Vec4f>& controlPoints_, const std::vector<float>& knotVector_, const unsigned int degree_);

	// returns false if the knot vector is not sorted or if the dimensions of knot vector, control points and degree do not match
	bool isValidNURBS();

	// insert a knot with deBoor algorithm. returns false, if newKnot is not within begin and end parameter.
	bool insertKnot(const float newKnot);

	// evaluate the curve at parameter t with deBoor (inserting a knot until its multiplicity is p). also returns the tangent at the evaluated point.
	Vec4f evaluteDeBoor(const float t, Vec4f& tangent);

private:

	// find the index k in knot vector with u in [u_k, u_k+1). returns -1 on error.
	int getIndex(const float u);

	// returns the multiplicity of knot u. returns 0 if u not in U. also returns index k so that u in [u_k, u_k+1)
	unsigned int getMultiplicityAndIndex(const float u, int &k);

};

// ostream << operator. E.g. use "std::cout << nurbs << std::endl;"
std::ostream& operator<< (std::ostream& os, NURBS_Curve& nurbsCurve);

#endif