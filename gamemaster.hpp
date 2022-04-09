#pragma once

class Gamemaster{
public:
  Gamemaster(Gamemaster_data* gamemaster_data);
  void draw_self(SDL_Texture* texture);
  void add_cell(Cell* cell);
  void sort_cells();

private:
  std::vector<Cell*> cells;
  SDL_Renderer* renderer;
  double xoff;
  double yoff;
  int WIDTH;
  int HEIGHT;
  double scale;
};
