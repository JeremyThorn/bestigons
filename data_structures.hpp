#pragma once

enum class Liquid_type {WATER, ACID, LAVA};
enum class Damage_type {CUT, IMP, CRUSH, PI, FIRE, ACID, ICE};

class Gamemaster;
class Cell;
class Obstacle{
  double height = 0;
  double damage = 0;
  Liquid_type liquid_type = Liquid_type::WATER;
  double movement_cost = 0;
};
struct Liquid {
  double height = 0;
  double damage = 0;
  Liquid_type liquid_type = Liquid_type::WATER;
  double movement_cost = 0;
};
struct Item;
