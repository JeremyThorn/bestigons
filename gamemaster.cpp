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
    cell->draw_self(texture,scale,xoff,yoff,angle);
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


void Gamemaster::zoom(double in_zoom, Vec2 zoom_vec){
  transform = transform*in_zoom;
  offset_n_scale = in_zoom*offset_n_scale + (-in_zoom+1)*zoom_vec;
  scale = scale*in_zoom;
  give_transform();
  give_offset_n_scale();
}

void Gamemaster::set_offset(Vec2 in_offset){
  offset_n_scale = offset_n_scale + in_offset;
  give_offset_n_scale();
}

void Gamemaster::rotate(double in_angle){
  angle = angle+in_angle;
  if(angle > M_PI*2){
    angle = angle - M_PI*2;
  }
  if(angle < 0){
    angle = angle + M_PI*2;
  }
}

void Gamemaster::get_clicked(Vec2 mousepos){
  //These two lines are to rescale sp that we a relative to the center of the
  //hex, rather than the top left hand corner (where the rect cood is).
  mousepos.x -= scale;
  mousepos.y -= scale*sqrt(3)/2;
  //Transform to grid space.
  Vec2 grid_coord = invert(transform)*(mousepos - offset_n_scale);
  grid_coord.x=round(grid_coord.x); grid_coord.y=round(grid_coord.y);
  std::cout << grid_coord << std::endl;
  Vec2 step_down_line = {-1, 1};
  Vec2 left_offset = {0, -1};
  Vec2 right_offset = {1, 0};
  std::vector<Vec2> line;
  for(int i = 3; i >= -3; i--){
    line.push_back(grid_coord+(double)i*step_down_line);
    line.push_back(grid_coord+(double)i*step_down_line + left_offset);
    line.push_back(grid_coord+(double)i*step_down_line + right_offset);
  }
  std::sort(line.begin(),line.end(), comp_coord);
  std::cout << std::endl;
  for(Vec2 coord : line){
    std::cout << coord << std::endl;
  }
  //auto old_it = cells.begin();
  Cell* selected_cell;
  for(Vec2 coord : line){

    const auto it = find_if(cells.begin(), cells.end(), [coord](const Cell* cell) {return cell->return_coords() == coord;});

    if (it != cells.end())
    {
      std::cout << std::endl;
      Vec2 test_coords;
      double test_height;
      (*it)->get_coords(&test_coords);
      (*it)->get_height(&test_height);
      std::cout << test_height << std::endl;
      Vec2 height_mousepos = {mousepos.x, mousepos.y+test_height*scale/50};
      Vec2 test_grid_coord_unround = invert(transform)*(height_mousepos - offset_n_scale);
      Vec2 test_grid_coord;
      test_grid_coord.x=round(test_grid_coord_unround.x); test_grid_coord.y=round(test_grid_coord_unround.y);
      std::cout << test_grid_coord_unround << std::endl;
      std::cout << height_mousepos << std::endl;
      std::cout << test_coords << std::endl;
      if (test_grid_coord == test_coords){
        selected_cell = (*it);
        break;
      }
      //old_it = it;
    }
  }

}
