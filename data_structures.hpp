#pragma once

enum class Liquid_type {WATER, ACID, LAVA};
enum class Damage_type {CUT, IMP, CRUSH, PI, HEAT, ACID, COLD, WATER, VOID, LIGHT};
enum class Floor_type {MUD, SAND, GRASS, STONE, BRIMSTONE};

class Gamemaster;
class Cell;

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

Matrix22 operator*(const Matrix22& m, const Vec2& v)
{
  Vec2 ans;
  ans.x = m.a*v.x + m.b*v.y;
  ans.y = m.c*v.x + m*d*v.y;
  return ans;
}

Vec2 operator+( const Vec2& v1, const Vec2& v2 )
{
  Vec2 ans;
  ans.x = v1.x + v2.x;
  ans.y = v1.y + v2.y;
  return ans;
}

struct Obstacle{
  double height;
  double damage;
  double health;
  double* damage_resist;
  Damage_type damage_type = Damage_type::CUT;
  double movement_cost;
};

struct Liquid {
  double height;
  double damage;
  Damage_type damage_type = Damage_type::WATER;
  Liquid_type liquid_type = Liquid_type::WATER;
  double movement_cost;
};

struct Item;
