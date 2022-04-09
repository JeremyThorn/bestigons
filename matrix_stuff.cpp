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

void invert(Matrix22 m, Matrix22* ans){
  double det = 1.0/(m.a*m.d - m.b*m.c);
  ans->a = det*m.d;
  ans->b = det*-m.b;
  ans->c = det*-m.c;
  ans->d = det*m.a;
}

Vec2 operator*(const Matrix22& m, const Vec2& v)
{
  Vec2 ans;
  ans.x = m.a*v.x + m.b*v.y;
  ans.y = m.c*v.x + m.d*v.y;
  return ans;
}

Vec2 operator+( const Vec2& v1, const Vec2& v2 )
{
  Vec2 ans;
  ans.x = v1.x + v2.x;
  ans.y = v1.y + v2.y;
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
