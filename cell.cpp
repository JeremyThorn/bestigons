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
#include "gamemaster.hpp"

void Cell::draw_self(SDL_Texture* texture, double rad, double XOFF, double YOFF, double angle){
  //Matrix22 transform;
  //transform =
  //transform.a = cos(M_PI/4);
  //transform.b = sin(M_PI/4);
  //transform.c = -sin(M_PI/4)/sqrt(3);
  //transform.d = cos(M_PI/4)/sqrt(3);

  //THIS IS ACTUALLY SOO GOOD
  //Vec2 new_coord = transform*((2.95*rad*sqrt(1.0/2.0))*(coord));
  Vec2 new_coord = transform*(coord)+offset_n_scale;


  SDL_Rect hex_rect;
  //hex_rect.x = new_coord.x+XOFF - rad;
  //hex_rect.y = new_coord.y+YOFF-height - rad*sqrt(3)/2;
  hex_rect.x = new_coord.x;
  hex_rect.y = new_coord.y-height*rad/50;
  hex_rect.w = 2*rad;
  hex_rect.h = 2*rad*sqrt(3)/2*2.5;

  SDL_SetRenderTarget(renderer,texture);
  SDL_RenderCopy(renderer,floor_texture,NULL,&hex_rect);
  SDL_SetRenderTarget(renderer,NULL);
  SDL_RenderDrawPoint(renderer,hex_rect.x,hex_rect.y);
  //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawPoint(renderer,hex_rect.x+0.5*hex_rect.w,hex_rect.y+0.5*hex_rect.h/2.5);
  //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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
  pillar_texture = cell_data->pillar_texture;
  floor_type = cell_data->floor_type;
  damage_type = cell_data->damage_type;
}


void Cell::get_coords(Vec2* coords){
  coords->x = coord.x;
  coords->y = coord.y;
}

void Cell::get_height(double* out_height){
  *out_height = height;
}

Vec2 Cell::return_coords() const{
  return coord;
}

void Cell::set_transform(Matrix22 in_transform){
  transform.a = in_transform.a;
  transform.b = in_transform.b;
  transform.c = in_transform.c;
  transform.d = in_transform.d;
}

void Cell::set_offset_n_scale(Vec2 in_offset_n_scale){
  offset_n_scale.x = in_offset_n_scale.x;
  offset_n_scale.y = in_offset_n_scale.y;
}

bool comp_cell(Cell* c1, Cell* c2){
  Vec2 v1,v2;
  c1->get_coords(&v1);
  c2->get_coords(&v2);
  return v1 < v2;
}
