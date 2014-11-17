// ========================================================================= //
// Authors: Matthias Bein                                                    //
// mailto:matthias.bein@igd.fraunhofer.de                                    //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
//                                                                           //
// Creation Date: 29.10.2013                                                 //
// ========================================================================= //

#ifndef MATRIX_4_H
#define MATRIX_4_H

class Matrix4f;

#include "Vec4.h"
#include "Vec3.h"
#include "Quaternion.h"

class Matrix4f
{
public:

	// class data: 4 by 4 matrix of floats. row first order, so first index is the row, second index the column.
	float values[4][4];

	// constructor generates eye-matrix by default
	Matrix4f();

	// constructor sets every entry to val
	Matrix4f(float val);

	// matrix matrix multiplication. uses this matrix as left one and the argument rightMatrix as right one
	Matrix4f operator* (const Matrix4f& rightMatrix) const;

	// matrix vector multiplication. multiplies this matrix with vec
	Vec4f operator* (const Vec4f& vec) const;

	// returns a matrix for translation. Use "Matrix4f matrix = Matrix4f::translationMatrix(tx, ty, tz);"
	static Matrix4f translationMatrix(float tx, float ty, float tz);

	// TODO: implement more basis transformation matrices
	// ==================================================
	static Matrix4f rotateX(float angle);

	static Matrix4f rotateY(float angle);

	static Matrix4f rotateZ(float angle);

	static Matrix4f rotate(const Quaternion& quaternion);

	static Matrix4f scale(float s);

	static Matrix4f scale(float x, float y, float z);
	// ==================================================

};

// ostream << operator. E.g. use "std::cout << matrix << std::endl;"
std::ostream& operator<< (std::ostream& os, const Matrix4f& matrix);

#endif