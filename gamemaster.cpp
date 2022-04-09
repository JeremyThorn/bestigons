#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <signal.h>
#include "matrix_stuff.hpp"
#include "data_structures.hpp"
#include "cell.hpp"
#include "gamemaster.hpp"



Gamemaster::Gamemaster(Gamemaster_data* gamemaster_data){
  renderer = gamemaster_data->renderer;
  WIDTH = gamemaster_data->WIDTH;
  HEIGHT = gamemaster_data->HEIGHT;
  xoff = WIDTH/2;
  yoff = HEIGHT/2;
  scale = gamemaster_data->scale;
  transform = gamemaster_data->transform;
  offset_n_scale = gamemaster_data->offset_n_scale;
}

void Gamemaster::add_cell(Cell* cell){
  cells.push_back(cell);
}


void Gamemaster::draw_self(SDL_Texture* texture){
  for(Cell* cell : cells){
    cell->draw_self(texture,scale,xoff,yoff);
  }
}

void Gamemaster::sort_cells(){
  std::sort(cells.begin(),cells.end(),comp_cell);

}

void Gamemaster::get_transform(Matrix22* out_transform){
  out_transform->a = transform.a;
  out_transform->b = transform.b;
  out_transform->c = transform.c;
  out_transform->d = transform.d;
}

void Gamemaster::set_transform(Matrix22 in_transform){
  transform.a = in_transform.a;
  transform.b = in_transform.b;
  transform.c = in_transform.c;
  transform.d = in_transform.d;
}

void Gamemaster::give_transform(){
  for(Cell* cell : cells){
    cell->set_transform(transform);
  }
}

void Gamemaster::give_offset_n_scale(){
  for(Cell* cell : cells){
    cell->set_offset_n_scale(offset_n_scale);
  }
}

void Gamemaster::get_clicked(Vec2 mousepos){
  Vec2 grid_coord = invert(transform)*(mousepos - offset_n_scale);
  grid_coord.x=round(grid_coord.x); grid_coord.y=round(grid_coord.y);
  std::cout << grid_coord << std::endl;

}
