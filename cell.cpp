void Cell::draw_self(SDL_Texture* texture, double rad){
  SDL_Rect hex_rect;
  hex_rect.x = x-rad;
  hex_rect.y = y-rad;
  hex_rect.w = 2*rad;
  hex_rect.h = 2*rad;

  SDL_SetRenderTarget(renderer,texture)
  SDL_RenderCopy(renderer,hex_texture,NULL,&hex_rect)
  SDL_SetRenderTarget(renderer,NULL)

}
