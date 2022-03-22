#pragma once

class Liquid{
public:
  void get_height(double* height);

  void set_height(double height);

  void get_damage(double* damage);

  void set_damage(double damage);

  void get_movement_cost(double* movement_cost);

  void set_movement_cost(double movement_cost);

  void get_liquid_type(Liquid_type* liquid_type);

  void set_liquid_type(Liquid_type liquid_type);

private:
  double height = 0;
  double damage = 0;
  Liquid_type liquid_type = Liquid_type::WATER;
  double movement_cost = 0;
};
