#pragma once

enum class Liquid_type {WATER, ACID, LAVA};
enum class Damage_type {CUT, IMP, CRUSH, PI, HEAT, ACID, COLD, WATER, VOID, LIGHT};

class Gamemaster;
class Cell;

struct Obstacle{
  double height;
  double damage;
  double health;
  double* damage_resist;
  Damage_type damage_type;
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
