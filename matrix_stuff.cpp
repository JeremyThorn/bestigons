#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <signal.h>
#include "matrix_stuff.hpp"
#include "data_structures.hpp"
#include "cell.hpp"
#include "gamemaster.hpp"

Matrix22 invert(Matrix22 m){
  Matrix22 ans;
  double det = 1.0/(m.a*m.d - m.b*m.c);
  ans.a = det*m.d;
  ans.b = det*-m.b;
  ans.c = det*-m.c;
  ans.d = det*m.a;
  return ans;
}

Vec2 operator*(const Matrix22& m, const Vec2& v)
{
  Vec2 ans;
  ans.x = m.a*v.x + m.b*v.y;
  ans.y = m.c*v.x + m.d*v.y;
  return ans;
}

Matrix22 operator*(const Matrix22& m, const double& d){
  Matrix22 ans;
  ans.a = m.a*d;
  ans.b = m.b*d;
  ans.c = m.c*d;
  ans.d = m.d*d;
  return ans;
}

Matrix22 operator*(const Matrix22& m1, const Matrix22& m2){
  Matrix22 ans;
  ans.a = m1.a*m2.a + m1.b*m2.c;
  ans.b = m1.a*m2.b + m1.b*m2.d;
  ans.c = m1.c*m2.a + m1.d*m2.c;
  ans.d = m1.d*m2.d + m1.c*m2.b;
  return ans;
}

Vec2 operator+( const Vec2& v1, const Vec2& v2 )
{
  Vec2 ans;
  ans.x = v1.x + v2.x;
  ans.y = v1.y + v2.y;
  return ans;
}

Vec2 operator-( const Vec2& v1, const Vec2& v2 )
{
  Vec2 ans;
  ans.x = v1.x - v2.x;
  ans.y = v1.y - v2.y;
  return ans;
}

Vec2 operator*(const double& d, const Vec2& v)
{
  Vec2 ans;
  ans.x = d*v.x;
  ans.y = d*v.y;
  return ans;
}

Vec2 operator+( const double& d, const Vec2& v )
{
  Vec2 ans;
  ans.x = v.x + d;
  ans.y = v.y + d;
  return ans;
}

bool operator>( const Vec2& v1, const Vec2& v2 )
{
  return (-v1.x+v1.y) > (v2.y-v2.x);
}

bool operator<( const Vec2& v1, const Vec2& v2 )
{
  return (-v1.x+v1.y) < (v2.y-v2.x);
}

bool operator==( const Vec2& v1, const Vec2& v2 )
{
  if(v1.x == v2.x && v1.y == v2.y){
    return true;
  }
  else{
    return false;
  }
}

std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix22& m)
{
  os << "[[" << m.a << ", " << m.b << "]" << std::endl << " [" << m.c << ", " << m.d << "]]";
  return os;
}

bool comp_coord(Vec2 v1, Vec2 v2){
  return v1 > v2;
}
