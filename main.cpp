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



const int WIDTH = 1400;
const int HEIGHT = 900;

int main(int argc, char *argv[]) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;


  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }
	int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
      printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
      return 1;
  }

  window = SDL_CreateWindow("Geam",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH, HEIGHT,SDL_WINDOW_OPENGL);

  if(window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  texture  = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);

  SDL_Event event;

  //TEST AREA STARTS HERE

  Gamemaster_data gd;
  gd.renderer=renderer;
  gd.WIDTH = WIDTH;
  gd.HEIGHT = HEIGHT;
  gd.transform = {cos(M_PI/4), sin(M_PI/4), -sin(M_PI/4)/sqrt(3), cos(M_PI/4)/sqrt(3)};
  Gamemaster* gm = new Gamemaster(&gd);

  SDL_Texture* grass_texture = IMG_LoadTexture(renderer, "tile_l.png");
  if(grass_texture==NULL){
    printf("Dwarfboi texture failed to load");
    exit(1);
  }

  int areas = 30;

  for(int i = 0;i < areas; i++){
    for(int j = 0;j < areas; j++){
      Cell_data test_cell_data;
      test_cell_data.coord.x=(int)(i-areas/2);
      test_cell_data.coord.y=(int)(j-areas/2);
      test_cell_data.movement_cost = 0;
      test_cell_data.damage = 0;
      test_cell_data.height = 0;
      if( i == 15 && j == 15){
        test_cell_data.height = 20;
      }
      if( i ==17 && j == 17){
        test_cell_data.height = -20;
      }
      if(i == 13 && j == 13){
        test_cell_data.height = -40;
      }
      if(i+1 == 13 || i-1 == 13 || i == 13){
        if(j+1 == 13 || j-1 == 13 || j == 13)
          if((i-13)*(j-13)<=0 && (j != 13 || i != 13)){
            test_cell_data.height = -20;
          }
      }
      if(i == 19 && j == 19){
        test_cell_data.height = -100;
      }
      test_cell_data.renderer = renderer;
      test_cell_data.floor_texture = grass_texture;

      gm->add_cell(new Cell(&test_cell_data));
    }
  }
  gm->sort_cells();
  gm->set_transform();


  //TEST AREA ENDS HERE


  while(1) {
    gm->draw_self(texture);

    SDL_RenderPresent(renderer);


    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
      }
      if(event.type == SDL_KEYDOWN){

      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
        }

      }
      if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
        }

      }
      if(event.type == SDL_MOUSEWHEEL){
      }
    }
  }
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
