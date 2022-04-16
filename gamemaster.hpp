#pragma once

class Gamemaster{
public:
  Gamemaster(Gamemaster_data* gamemaster_data);
  void draw_self(SDL_Texture* texture);
  void add_cell(Cell* cell);
  void sort_cells();
  void get_clicked(Vec2 mousepos);
  void round_to_cell(Vec2* gridpos);
  void get_transform(Matrix22* out_transform);
  void set_transform(Matrix22 in_transform);
  void give_transform();
  void give_offset_n_scale();
  void give_trans_n_offset_n_scale();
  void zoom(double zoom,Vec2 zoom_vec);
  void set_offset(Vec2 offset);
  void rotate(double angle, Vec2 rot_p);

  //Just some test stuff
  void test_explosion();
  void perlin_noise(double mag,int lvl,double var);


private:
  std::vector<Cell*> cells;
  SDL_Renderer* renderer;
  double xoff;
  double yoff;
  double angle = 0;
  int WIDTH;
  int HEIGHT;
  double scale;
  Matrix22 transform = {0, 0, 0, 0};
  Vec2 offset_n_scale = {0, 0};
  Cell* selected_cell;
  int grid_size;


  SDL_Texture* grass_texture;
  SDL_Texture* pillar_texture;
  SDL_Texture* selector_texture;
};
