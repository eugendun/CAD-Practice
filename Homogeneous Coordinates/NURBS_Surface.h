#ifndef NURBS_SURFACE_H
#define NURBS_SURFACE_H

#include <stdlib.h>			// standard library
#include <vector>			// std::vector<>

#include "NURBS_Curve.h"
#include "Vec4.h"

class NURBS_Surface {

public:

	// class data:
	std::vector<std::vector<Vec4f>> controlPoints;	// control mesh, first index for v direction, second for u. So P[i] is a vector of control points in u direction. A vector of control points in v direction has to be generated manually.
	std::vector<float> knotVectorU;					// knot vector in u direction
	std::vector<float> knotVectorV;					// knot vector in v direction
	unsigned int degree;							// degree for both directions

	// empty constructor which creates a test surface
	NURBS_Surface();

	// constructor which takes given control mesh, knot vector U and V and degree
	NURBS_Surface(const std::vector<std::vector<Vec4f>>& controlPoints_, const std::vector<float>& knotVectorU_, const std::vector<float>& knotVectorV_, const unsigned int degree_);

	// returns false if the knot vector is not sorted or if the dimensions of knot vector, control points and p do not match
	bool isValidNURBS();

	// evaluate the curve at parameter t with deBoor (inserting a knot until its multiplicity is p). also returns the tangent at the evaluated point.
	Vec4f evaluteDeBoor(const float u, const float v, Vec4f& tangentU, Vec4f& tangentV);

};

// ostream << operator. E.g. use "std::cout << nurbs << std::endl;"
std::ostream& operator<< (std::ostream& os, NURBS_Surface& nurbsSurface);

#endif