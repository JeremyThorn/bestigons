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

Matrix22 invert(Matrix22 m);
double dot(Vec2 v1, Vec2 v2);

Vec2 operator*(const Matrix22& m, const Vec2& v);
Matrix22 operator*(const Matrix22& m, const double& d);

Matrix22 operator*(const Matrix22& m1, const Matrix22& m2);

Vec2 operator+( const Vec2& v1, const Vec2& v2 );
Vec2 operator-( const Vec2& v1, const Vec2& v2 );

Vec2 operator*(const double& d, const Vec2& v);

Vec2 operator+( const double& d, const Vec2& v );

bool operator<(const Vec2& v1, const Vec2& v2);
bool operator==( const Vec2& v1, const Vec2& v2 );

std::ostream& operator<<(std::ostream& os, const Vec2& v);

std::ostream& operator<<(std::ostream& os, const Matrix22& m);

bool comp_coord(Vec2 v1, Vec2 v2);
