#pragma once

struct Vec2{
  double x;
  double y;
};

struct Matrix22{
  double a;
  double b;
  double c;
  double d;
};

void invert(Matrix22 m, Matrix22* ans);

Vec2 operator*(const Matrix22& m, const Vec2& v);

Vec2 operator+( const Vec2& v1, const Vec2& v2 );

Vec2 operator*(const double& d, const Vec2& v);

Vec2 operator+( const double& d, const Vec2& v );

std::ostream& operator<<(std::ostream& os, const Vec2& v);

std::ostream& operator<<(std::ostream& os, const Matrix22& m);
