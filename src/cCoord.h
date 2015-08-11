/* 
 * File:   cCoord.h
 * Author: luizfelipe
 *
 * Created on October 28, 2010, 11:54 PM
 */

#ifndef COORD_H
#define	COORD_H

#include "math.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
template<class T> class cCoord
{
 public:
  T x, y, z;

  cCoord(T X = 0, T Y = 0, T  Z= 0) : x(X), y(Y), z(Z) {}
  cCoord(const cCoord<T>& coord) {*this = coord;}

  void operator=(const cCoord<T>& coord)
  {x = coord.x; y = coord.y; z = coord.z;}
  void operator+=(const cCoord<T>& coord)
  {x += coord.x; y += coord.y; z += coord.z;}
  void operator-=(const cCoord<T>& coord)
  {x -= coord.x; y -= coord.y; z -= coord.z;}
  void operator*=(double v)
  {x *= v; y *= v; z *= v;}
  void operator/=(double v)
  {x /= v; y /= v; z /= v;}

  void to_vec(T *v)
  {
   v[0] = x;
   v[1] = y;
   v[2] = z;
  }

  friend cCoord<T> operator+(const cCoord<T>& a, const cCoord<T>& b)
  {cCoord<T> c; c.x = a.x + b.x; c.y = a.y + b.y; c.z = a.z + b.z; return c;}
  friend cCoord<T> operator-(const cCoord<T>& a, const cCoord<T>& b)
  {cCoord<T> c; c.x = a.x - b.x; c.y = a.y - b.y; c.z = a.z - b.z; return c;}
  friend cCoord<T> operator*(const cCoord<T>& v, T c)
  {cCoord<T> w; w.x = v.x * c; w.y = v.y * c; w.z = v.z * c; return w;}
  friend bool operator==(const cCoord<T>& a, const cCoord<T>& b)
  {return a.x == b.x && a.y == b.y && a.z == b.z;}
};

//cCoord<double> Normalize(const cCoord<double>&);
//cCoord<double> CrossProd(const cCoord<double>&, const cCoord<double>&);
//inline double DotProd(const cCoord<double>& a, const cCoord<double>& b) {return a.x * b.x + a.y * b.y + a.z * b.z;}
//inline double SqrNorm(const cCoord<double>& a) {return DotProd(a, a);}
//double Module(const cCoord<double>& a) {return sqrt(DotProd(a, a));}
//double Module2D(const cCoord<double>& a) {return sqrt((a.x*a.x)+(a.y*a.y));}
//cCoord<double> Rotate(const cCoord<double>&, const cCoord<double>&, double, int);
//cCoord<double> Rotate(const cCoord<double>&, double, int);
//cCoord<double> LinearInterpol(double, const cCoord<double>&, const cCoord<double>&);

#endif	/* COORD_H */

