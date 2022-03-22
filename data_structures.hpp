#pragma once

enum class Liquid_type {WATER, ACID, LAVA};

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
