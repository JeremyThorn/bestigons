#pragma once

class Gamemaster{
public:
  Gamemaster(Gamemaster_data* gamemaster_data);
  void draw_self(SDL_Texture* texture);
  void add_cell(Cell* cell);
  void sort_cells();
  void get_clicked(Vec2 mousepos);
  void get_transform(Matrix22* out_transform);
  void set_transform(Matrix22 in_transform);
  void give_transform();
  void give_offset_n_scale();

private:
  std::vector<Cell*> cells;
  SDL_Renderer* renderer;
  double xoff;
  double yoff;
  int WIDTH;
  int HEIGHT;
  double scale;
  Matrix22 transform = {0, 0, 0, 0};
  Vec2 offset_n_scale = {0, 0};
};
