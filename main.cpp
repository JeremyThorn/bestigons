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


  SDL_Event event;

  bool panning = false;

  Vec2 pos = {0, 0};
  Vec2 old_pos = {0, 0};

  //TEST AREA STARTS HERE

  Gamemaster_data gd;
  gd.renderer=renderer;
  gd.WIDTH = WIDTH;
  gd.HEIGHT = HEIGHT;
  gd.scale = 50;
  Matrix22 rotator = {cos(M_PI/4), sin(M_PI/4), -sin(M_PI/4)/sqrt(3), cos(M_PI/4)/sqrt(3)};
  gd.transform = rotator*(3*gd.scale*sqrt(1.0/2.0));
  gd.offset_n_scale = {gd.WIDTH/2 - gd.scale, gd.HEIGHT/2 - gd.scale*sqrt(3)/2};
  gd.grid_size = 50;

  Gamemaster* gm = new Gamemaster(&gd);


  /*
  int areas = 30;

  for(int i = 0;i < areas; i++){
    for(int j = 0;j < areas; j++){
      Cell_data test_cell_data;
      test_cell_data.coord.x=(int)(i-areas/2);
      test_cell_data.coord.y=(int)(j-areas/2);
      test_cell_data.movement_cost = 0;
      test_cell_data.damage = 0;
      test_cell_data.height = -1;
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
      test_cell_data.pillar_texture = pillar_texture;
      test_cell_data.selector_texture = selector_texture;

      gm->add_cell(new Cell(&test_cell_data));
    }
  }
  */

  gm->give_transform();
  gm->give_offset_n_scale();
  gm->sort_cells();




  //TEST AREA ENDS HERE

  SDL_Texture *texture  = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);
  while(1) {

    int x, y;
    SDL_GetMouseState(&x, &y);
    pos.x = (double)x; pos.y = (double)y;
    gm->draw_self(texture);

    SDL_Rect test;
    test.x=0;
    test.y=0;
    test.w=WIDTH;
    test.h=HEIGHT;
    SDL_RenderCopy(renderer,texture,&test,&test);

    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderTarget(renderer,texture);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer,NULL);

    if(panning){
      Vec2 diff;
      diff = pos-old_pos;
      gm->set_offset(diff);
      old_pos.x = pos.x;
      old_pos.y = pos.y;
    }

    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Q]){
      gm->rotate(0.03,pos);
    }
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_E]){
      gm->rotate(-0.03,pos);
    }

    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
      }
      if(event.type == SDL_KEYDOWN){
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]){
          gm->test_explosion();
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_P]){
          gm->perlin_noise(100,6,0.5);
        }

      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
          panning = true;
          old_pos.x = pos.x;
          old_pos.y = pos.y;
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
        }

      }
      if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
          //Vec2 pos = {0, 0};
          //int x, y;
          //SDL_GetMouseState(&x, &y);
          //pos.x = (double)x; pos.y = (double)y;
          panning = false;
          gm->get_clicked(pos);
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
        }

      }
      if(event.type == SDL_MOUSEWHEEL){
        gm->zoom(pow(1.1,event.wheel.y),pos);
      }
    }

  }
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
