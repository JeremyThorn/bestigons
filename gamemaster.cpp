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
  scale = 50;
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
