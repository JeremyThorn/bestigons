#pragma once

class Cell{
public:
  void set_movement_cost(int movement_cost);
  void get_movement_cost(int* movement_cost);

  void get_damage(double* damage);
  void set_damage(double damage);

  void get_height(double* height);
  void set_height(double height);

  void add_item(Item* item);
  void remove_item(Item* item);

  void set_obstacle(Obstacle obstacle);
  void set_liquid(Liquid liquid);
private:
  std::vector<Item*> inventory;
  std::vector<double> coord;
  int movement_cost = 0;
  double damage = 0.0;
  double height = 0.0;
  Obstacle obstacle;
  Liquid liquid;
};
