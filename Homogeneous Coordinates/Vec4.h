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

#ifndef VEC4_H
#define VEC4_H

#include <math.h>
#include <string>

// embed in namespace std to not mix up with OpenSG Vec4 or any others
//namespace std {

template<class T>
class Vec4
{
public:

	// values
	T x,y,z,w;

	// empty constructor. sets values to 0
	Vec4() : x(0), y(0), z(0), w(0)
	{
	}

	// constructor with 3 values (v1,v2,v3,v4)
	Vec4(const T v1, const T v2, const T v3, const T v4) : x(v1), y(v2), z(v3), w(v4)
	{
	}

	// copy constuctor
	Vec4(const Vec4 & other) : x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	// returns i-th komponent (i=0,1,2,3) (RHS array operator)
	const T operator[] (unsigned int i) const
	{
		return *(&x+i);
	}

	// LHS array operator
	T & operator [] (unsigned int i)
	{
		return *(&x+i);
	}

	// Vec4 == Vec4 (equals)
	bool operator== (const Vec4 &v) const
	{
		if (v.x == x && v.y == y && v.z == z && v.w == w) return true;
		else return false;
	}
	// Vec4 != Vec4 (not equal)
	bool operator!= (const Vec4 &v) const
	{
		return !(*this == v);
	}

	// Vec3 = Vec3 + Vec3 (vector addition)
	Vec4 operator+ (const Vec4 &v) const
	{
		Vec4 result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;
		result.w = w + v.w;
		return result;
	}

	// Vec3 = Vec3 - Vec3 (normal vector subtraction)
	Vec4 operator- (const Vec4 &v) const
	{
		Vec4 result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;
		result.w = w - v.w;
		return result;
	}

	// Vec3 = Vec3 * T (scalar multiplication)
	Vec4 operator* (const T &f) const
	{
		Vec4 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		result.w = w * f;
		return result;
	}
	
	// returns euclidic length (sqrt(x*x + y*y + z*z + w*w))
	float length() const
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}

	// returns squared euclidic length (x*x + y*y + z*z + w*w)
	T sqlength() const
	{
		return x*x + y*y + z*z + w*w;
	}

	// returns distance to v
	float distance(const Vec4 &v) const
	{
		return (v - *this).length();
	}

	// homogenizes this vector (division by w). returns false when w is < 0.00001
	bool homogenize()
	{
		if (fabs(w) < 0.00001) return false;
		x /= w;
		y /= w;
		z /= w;
		w = 1;
		return true;
	}

	// returns homogenized vector but does not change this Vec4. returns unhomogenized vector if w is < 0.00001
	Vec4 homogenized() const
	{
		if (fabs(w) < 0.00001) return *this;
		return Vec4(x/w, y/w, z/w, 1);
	}

	// sets values to 0
	void clear()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	// set values
	void set(T _x, T _y, T _z, T _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void set(const Vec4 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

}; // class Vec4

// Vec4 = T * Vec4 (scalar multiplication)
template <class T>
Vec4<T> operator* (const T &f, const Vec4<T> &v)
{
	return v * f;
}

// ostream << operator
template< class T>
std::ostream& operator<< (std::ostream& os, const Vec4<T> & v)
{
	os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
	return os;
}

// predefined typedefs
typedef Vec4<float>         Vec4f;
typedef Vec4<int>           Vec4i;
typedef Vec4<unsigned int>  Vec4ui;
typedef Vec4<double>        Vec4d;

//} // namespace std

#endif