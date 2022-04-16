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

  Vec2 new_coord = transform*(coord)+offset_n_scale;

  double angle_60 = angle;
  bool is_in_range = false;
  while(!is_in_range){
    if(angle_60 > M_PI/3){
      angle_60 = angle_60 - M_PI/3;
    }
    else if(angle_60 < 0){
      angle_60 = angle_60 + M_PI/3;
    }
    else{
      is_in_range=true;
    }
  }

  SDL_Rect hex_rect;
  hex_rect.x = new_coord.x -rad;
  hex_rect.y = new_coord.y-height*rad/50 - rad*sqrt(3)/2;
  hex_rect.w = 2*rad;
  hex_rect.h = 2*rad*sqrt(3)/2;

  double cosine_boy = std::max(cos(angle_60),std::max(cos(angle_60+M_PI/3),cos(angle_60-M_PI/3)));
  double sinny_boy = sqrt(1-cosine_boy*cosine_boy);

  if(angle_60 < M_PI/6){
    sinny_boy = -sinny_boy;
  }
  SDL_Rect pillar_rect_l;

  pillar_rect_l.x = new_coord.x+rad*(-cosine_boy);
  pillar_rect_l.y = new_coord.y-height*rad/50+sinny_boy*rad;
  pillar_rect_l.w = rad*cosine_boy+2;
  pillar_rect_l.h = 2*rad*2-sinny_boy*rad;

  SDL_Rect pillar_rect_r;

  pillar_rect_r.x = new_coord.x;
  pillar_rect_r.y = new_coord.y -height*rad/50-sinny_boy*rad;
  pillar_rect_r.w = rad*cosine_boy;
  pillar_rect_r.h = 2*rad*2+sinny_boy*rad;

  //std::cout << 360*angle/(M_PI*2) << std::endl;
  SDL_SetRenderTarget(renderer,texture);
  SDL_RenderCopy(renderer,pillar_texture,NULL,&pillar_rect_l);
  SDL_RenderCopyEx(renderer,pillar_texture,NULL,&pillar_rect_r,0,NULL,SDL_FLIP_HORIZONTAL);
  SDL_RenderCopyEx(renderer,floor_texture,NULL,&hex_rect,360*angle/(M_PI*2),NULL,SDL_FLIP_NONE);
  SDL_SetRenderTarget(renderer,NULL);
  //SDL_RenderDrawPoint(renderer,hex_rect.x,hex_rect.y);
  //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  //SDL_RenderDrawPoint(renderer,hex_rect.x+0.5*hex_rect.w,hex_rect.y+0.5*hex_rect.h/2.5);
  //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

void Cell::draw_selector(SDL_Texture* texture,SDL_Texture* selector_texture, double rad, double XOFF, double YOFF, double angle){
  Vec2 new_coord = transform*(coord)+offset_n_scale;

  double angle_60 = angle;
  bool is_in_range = false;
  while(!is_in_range){
    if(angle_60 > M_PI/3){
      angle_60 = angle_60 - M_PI/3;
    }
    else if(angle_60 < 0){
      angle_60 = angle_60 + M_PI/3;
    }
    else{
      is_in_range=true;
    }
  }


  SDL_Rect selector_rect;
  double selector_scale_factor = 2.4;
  selector_rect.x = new_coord.x - selector_scale_factor/2.0*rad;
  selector_rect.y = new_coord.y-height*rad/50 - selector_scale_factor/2.0*rad*sqrt(3)/2;
  selector_rect.w = selector_scale_factor*rad;
  selector_rect.h = selector_scale_factor*rad*sqrt(3)/2;

  //std::cout << 360*angle/(M_PI*2) << std::endl;
  SDL_SetRenderTarget(renderer,texture);

  SDL_RenderCopyEx(renderer,selector_texture,NULL,&selector_rect,360*angle/(M_PI*2),NULL,SDL_FLIP_NONE);

  SDL_SetRenderTarget(renderer,NULL);
  //SDL_RenderDrawPoint(renderer,hex_rect.x,hex_rect.y);
  //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  //SDL_RenderDrawPoint(renderer,hex_rect.x+0.5*hex_rect.w,hex_rect.y+0.5*hex_rect.h/2.5);
  //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

Cell::Cell(Cell_data* cell_data){
  coord = cell_data->coord;
  movement_cost = cell_data->movement_cost;
  damage = cell_data->damage;
  height = cell_data->height;
  //std::cout << height << std::endl;
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
  //std::cout << height << std::endl;
  *out_height = height;
}

void Cell::chng_height(double c_height){
  height = height+c_height;
}


void Cell::set_height(double in_height){
  height = in_height;
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

void Cell::get_real_height(double* y){
  Vec2 new_coord = transform*(coord)+offset_n_scale;
  *y = new_coord.y;


}

bool comp_cell_y(Cell* c1, Cell* c2){
  double y1,y2;
  c1->get_real_height(&y1);
  c2->get_real_height(&y2);
  return y1 < y2;
}

bool comp_cell(Cell* c1, Cell* c2){
  Vec2 v1,v2;
  c1->get_coords(&v1);
  c2->get_coords(&v2);
  return v1 < v2;
}
