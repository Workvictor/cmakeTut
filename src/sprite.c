#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

void
sprite_create(SDL_Renderer* renderer, char* fileName)
{
  SDL_Rect srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = 32;
  srcRect.h = 32;
  SDL_Rect dstRect;
  dstRect.x = 0;
  dstRect.y = 0;
  dstRect.w = 32;
  dstRect.h = 32;
  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(renderer, fileName);
  if (texture == NULL) {
    printf("textue error %s\n", SDL_GetError());
  }
}