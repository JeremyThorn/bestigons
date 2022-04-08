#pragma once

enum class Liquid_type {WATER, ACID, LAVA};
enum class Damage_type {CUT, IMP, CRUSH, PI, HEAT, ACID, COLD, WATER, VOID, LIGHT};
enum class Floor_type {MUD, SAND, GRASS, STONE, BRIMSTONE};

class Gamemaster;
class Cell;

SDL_Point operator+( const SDL_Point& v1, const SDL_Point& v2 )
{
    SDL_Point ans;
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
