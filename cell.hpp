#pragma once

class Cell{
public:
  void set_movement_cost(int movement_cost);
  void get_movement_cost(int* movement_cost);

  void get_damage(double* damage);
  void set_damage(double damage);

  void get_height(double* height);
  void set_height(double height);

  
private:
  std::vector<Item> inventory;
  int movement_cost = 0;
  double damage = 0.0;
  double height = 0.0;
  Obstacle obstacle;
  Liquid liquid;
};
