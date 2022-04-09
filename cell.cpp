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
#include <signal.h>
#include "matrix_stuff.hpp"
#include "data_structures.hpp"
#include "cell.hpp"

void Cell::draw_self(SDL_Texture* texture, double rad, double XOFF, double YOFF){
  Matrix22 transform;
  transform.a = cos(M_PI/4);
  transform.b = sin(M_PI/4);
  transform.c = -sin(M_PI/4)/sqrt(3);
  transform.d = cos(M_PI/4)/sqrt(3);

  //THIS IS ACTUALLY SOO GOOD
  Vec2 new_coord = transform*(2*rad*sqrt(3/2)*(coord));


  SDL_Rect hex_rect;
  hex_rect.x = new_coord.x+XOFF;
  hex_rect.y = new_coord.y+YOFF+height;
  hex_rect.w = 2*rad;
  hex_rect.h = 2*rad*sqrt(3)/2;

  SDL_SetRenderTarget(renderer,texture);
  SDL_RenderCopy(renderer,floor_texture,NULL,&hex_rect);
  SDL_SetRenderTarget(renderer,NULL);

}


Cell::Cell(Cell_data* cell_data){
  coord = cell_data->coord;
  movement_cost = cell_data->movement_cost;
  damage = cell_data->damage;
  height = cell_data->height;
  obstacle = cell_data->obstacle;
  liquid = cell_data->liquid;
  renderer = cell_data->renderer;
  floor_texture = cell_data->floor_texture;
  floor_type = cell_data->floor_type;
  damage_type = cell_data->damage_type;
}
