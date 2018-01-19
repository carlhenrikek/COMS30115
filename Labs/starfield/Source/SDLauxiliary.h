#ifndef SDL_AUXILIARY_H
#define SDL_AUXILIARY_H

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <stdint.h>

typedef struct{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int height;
  int width;
  uint32_t *buffer;
} screen;

screen* InitializeSDL( int width, int height, bool fullscreen = false );
bool NoQuitMessageSDL();
void PutPixelSDL( screen *s, int x, int y, glm::vec3 color );
void SDL_Renderframe(screen *s);
void KillSDL(screen* s);
void SDL_SaveImage(screen *s, const char* filename);

void SDL_SaveImage(screen *s, const char* filename)
{
  uint32_t rmask, gmask, bmask, amask;

  if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
      amask = 0xff << 0;
      rmask = 0xff << 8;
      gmask = 0xff << 16;
      bmask = 0xff << 24;
    }
  else
    {
      amask = 0xff << 24;
      rmask = 0xff << 16;
      gmask = 0xff << 8;
      bmask = 0xff << 0;
    }

  SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)s->buffer, s->width, s->height,
					       32, s->width*sizeof(uint32_t),
					       rmask,gmask,bmask,amask);
  if(SDL_SaveBMP(surf, filename) !=0)
    {
      std::cout << "Failed to save image: "
		<< SDL_GetError() << std::endl;
      exit(1);
    }
  
}

void KillSDL(screen* s)
{
  delete[] s->buffer;
  SDL_DestroyTexture(s->texture);
  SDL_DestroyRenderer(s->renderer);
  SDL_DestroyWindow(s->window);
  SDL_Quit();
}

void SDL_Renderframe(screen* s)
{
  SDL_UpdateTexture(s->texture, NULL, s->buffer, s->width*sizeof(uint32_t));
  SDL_RenderClear(s->renderer);
  SDL_RenderCopy(s->renderer, s->texture, NULL, NULL);
  SDL_RenderPresent(s->renderer);
}

screen* InitializeSDL(int width,int height, bool fullscreen)
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) !=0)
    {
      std::cout << "Could not initialise SDL: "
		<< SDL_GetError() << std::endl;
      exit(1);
    }
  
  screen *s = new screen;
  s->width = width;
  s->height = height;
  s->buffer = new uint32_t[width*height];
  memset(s->buffer, 0, width*height*sizeof(uint32_t));
  
  uint32_t flags = SDL_WINDOW_OPENGL;
  if(fullscreen)
    {
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
  s->window = SDL_CreateWindow("COMS30115",
				      SDL_WINDOWPOS_UNDEFINED,
				      SDL_WINDOWPOS_UNDEFINED,
				      width, height,flags);
  if(s->window == 0)
    {
      std::cout << "Could not set video mode: "
	     << SDL_GetError() << std::endl;
      exit(1);
    }

  flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  s->renderer = SDL_CreateRenderer(s->window, -1, flags);
  if(s->renderer == 0)
    {
      std::cout << "Could not create renderer: "
	     << SDL_GetError() << std::endl;
      exit(1);
    }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(s->renderer, width,height);

  s->texture = SDL_CreateTexture(s->renderer,
				 SDL_PIXELFORMAT_ARGB8888,
				 SDL_TEXTUREACCESS_STATIC,
				 s->width,s->height);
  if(s->texture==0)
    {
      std::cout << "Could not allocate texture: "
	     << SDL_GetError() << std::endl;
      exit(1);
    }
  
  return s;
}

bool NoQuitMessageSDL()
{
  SDL_Event e;
  while( SDL_PollEvent(&e) )
    {
      if( e.type == SDL_QUIT )
	{
	  return false;
	}
      if( e.type == SDL_KEYDOWN )
	{
	  if( e.key.keysym.sym == SDLK_ESCAPE)
	    {
	      return false;
	    }
	}
    }
  return true;
}

void PutPixelSDL(screen* s, int x, int y, glm::vec3 colour)
{
  if(x<0 || x>=s->width || y<0 || y>=s->height)
    {
      std::cout << "apa" << std::endl;
      return;
    }
  uint32_t r = uint32_t( glm::clamp( 255*colour.r, 0.f, 255.f ) );
  uint32_t g = uint32_t( glm::clamp( 255*colour.g, 0.f, 255.f ) );
  uint32_t b = uint32_t( glm::clamp( 255*colour.b, 0.f, 255.f ) );

  s->buffer[y*s->width+x] = (128<<24) + (r<<16) + (g<<8) + b;
}


#endif
