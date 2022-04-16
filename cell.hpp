#pragma once

class Cell{
public:
  Cell(Cell_data* cell_data);
  void set_movement_cost(int movement_cost);
  void get_movement_cost(int* movement_cost);

  void get_damage(double* damage);
  void set_damage(double damage);

  void set_height(double height);
  
  void chng_height(double c_height);

  void add_item(Item* item);
  void remove_item(Item* item);

  void set_obstacle(Obstacle obstacle);
  void set_liquid(Liquid liquid);

  void draw_self(SDL_Texture* texture, double rad, double XOFF, double YOFF, double angle);
  void draw_selector(SDL_Texture* texture,SDL_Texture* selector_texture, double rad, double XOFF, double YOFF, double angle);

  void get_real_height(double* y);

  void get_coords(Vec2* coord);
  void get_height(double* out_height);
  Vec2 return_coords() const;
  void set_transform(Matrix22 in_transform);
  void set_offset_n_scale(Vec2 in_offset_n_scale);
private:
  std::vector<Item*> inventory;
  Vec2 coord;
  int movement_cost = 0;
  double damage = 0.0;
  double height = -1;
  Obstacle obstacle;
  Liquid liquid;
  SDL_Renderer* renderer;
  SDL_Texture* floor_texture;
  SDL_Texture* pillar_texture;
  Floor_type floor_type = Floor_type::GRASS;
  Damage_type damage_type = Damage_type::CUT;
  Matrix22 transform = {0, 0, 0, 0};
  Vec2 offset_n_scale = {0, 0};
};


bool comp_cell(Cell* c1, Cell* c2);
bool comp_cell_y(Cell* c1, Cell* c2);
