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

#include "Matrix4.h"

Matrix4f::Matrix4f()
{
	for(unsigned int row = 0; row < 4; ++row)
	{
		for(unsigned int column = 0; column < 4; ++column)
		{
			if(row == column)
				values[row][column] = 1.0f;
			else
				values[row][column] = 0.0f;
		}
	}
}

Matrix4f::Matrix4f(float val)
{
	for(unsigned int row = 0; row < 4; ++row)
	{
		for(unsigned int column = 0; column < 4; ++column)
		{
			values[row][column] = val;
		}
	}
}


Matrix4f Matrix4f::operator* (const Matrix4f& rightMatrix) const
{
	// start with 0-matrix
	Matrix4f result(0.0f);
	// TODO: implement matrix matrix multiplication
	// ============================================
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.values[i][k] += values[i][j] * rightMatrix.values[j][k];
			}
		}
	}
	// ============================================
	return result;
}

Vec4f Matrix4f::operator* (const Vec4f& vec) const
{
	// start with 0-vector
	Vec4f result;
	// TODO: implement matrix vector multiplication
	// ============================================
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i] += values[i][j] * vec[j];
		}
	}
	// ============================================
	return result;
}

std::ostream& operator<< (std::ostream& os, const Matrix4f& matrix)
{
	os  << matrix.values[0][0] << ", " << matrix.values[0][1] << ", " << matrix.values[0][2] << ", " << matrix.values[0][3] << std::endl
		<< matrix.values[1][0] << ", " << matrix.values[1][1] << ", " << matrix.values[1][2] << ", " << matrix.values[1][3] << std::endl
		<< matrix.values[2][0] << ", " << matrix.values[2][1] << ", " << matrix.values[2][2] << ", " << matrix.values[2][3] << std::endl
		<< matrix.values[3][0] << ", " << matrix.values[3][1] << ", " << matrix.values[3][2] << ", " << matrix.values[3][3];
	return os;
}

Matrix4f Matrix4f::translationMatrix(float tx, float ty, float tz)
{
	// start with eye matrix
	Matrix4f result;
	// enter translation components in last column
	result.values[0][3] = tx;
	result.values[1][3] = ty;
	result.values[2][3] = tz;
	return result;
}

// TODO: implement more basis transformation matrices
// ==================================================

// ==================================================