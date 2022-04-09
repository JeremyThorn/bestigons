#pragma once

enum class Liquid_type {WATER, ACID, LAVA};
enum class Damage_type {CUT, IMP, CRUSH, PI, HEAT, ACID, COLD, WATER, VOID, LIGHT};
enum class Floor_type {MUD, SAND, GRASS, STONE, BRIMSTONE};

class Gamemaster;
class Cell;

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

struct Cell_data {
  Vec2 coord;
  int movement_cost;
  double damage;
  double height;
  Obstacle obstacle;
  Liquid liquid;
  SDL_Renderer* renderer;
  SDL_Texture* floor_texture;
  Floor_type floor_type;
  Damage_type damage_type;
};

struct Gamemaster_data {
  SDL_Renderer* renderer;
  int WIDTH;
  int HEIGHT;
  Matrix22 transform;
  double scale;
  Vec2 offset_n_scale;
};

struct Item;
