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



  Cell_data test_cell_data;
  test_cell_data.coord =

  Cell test_cell = Cell();


  while(1) {


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
