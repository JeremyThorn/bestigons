#include <stdio.h>
#include <iostream>
#include <math.h>
#include "data_structures.hpp"
#include "matrix_stuff.hpp"

const double PI = 3.14159265;

int main(){
  double s = 0.8;
  double ang = 45;
  Matrix22 m = {s*cos(ang*PI/180), -sin(ang*PI/180), s*sin(ang*PI/180), cos(ang*PI/180)};
  Matrix22 im = {0, 0, 0, 0};
  invert(m, &im);
  std::cout << m << std::endl;
  std::cout << im << std::endl;
  Vec2 v = {1.0, 0.0};
  Vec2 ans = m*v;
  Vec2 ans2 = im*ans;
  std::cout << ans << std::endl;
  std::cout << ans2 << std::endl;
  return 0;
}
