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
#include <filesystem>

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

  window = SDL_CreateWindow("Obstacle drawing test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH, HEIGHT,SDL_WINDOW_OPENGL);

  if(window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  std::vector<SDL_Texture*> model;
  std::vector<SDL_Rect*> model_rects;

  for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("test_model")){
    //std::cout << dirEntry << std::endl;
    SDL_Texture* subtexture = IMG_LoadTexture(renderer, dirEntry);
    SDL_Rect* subrect;
    if(subtexture==NULL){
      printf("Dwarfboi texture failed to load");
      exit(1);
    }
    model.push_back(subtexture);
  }

  SDL_Event event;

  while(1) {
    SDL_Texture *texture  = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);

    for(SDL_Texture* subtexture : model){
      SDL_SetRenderTarget(renderer,texture);
      SDL_RenderCopy(renderer,subtexture,NULL,&pillar_rect_l);
      //SDL_RenderCopyEx(renderer,pillar_texture,NULL,&pillar_rect_r,0,NULL,SDL_FLIP_HORIZONTAL);
      //SDL_RenderCopyEx(renderer,floor_texture,NULL,&hex_rect,360*angle/(M_PI*2),NULL,SDL_FLIP_NONE);
      SDL_SetRenderTarget(renderer,NULL);
    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(texture);


    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Q]){
      //gm->rotate(0.01,pos);
    }
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_E]){
      //gm->rotate(-0.01,pos);
    }

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
