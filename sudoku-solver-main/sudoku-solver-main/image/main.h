#ifndef
#define

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void event_loop(SDL_Surface* surface);
SDL_Surface* load_image(char* filename);
Uint32 pixel_to_grayscale(Uint32 pixel, SDL_PixelFormat* format);
void surface_to_grayscale(SDL_Surface* surface);
void adaptative_threshhold(SDL_Surface* surface);
void invert(SDL_Surface* surface);
int flood_fill(SDL_Surface* surface, size_t x, size_t y, Uint32 color);
void get_grid(SDL_Surface* surface1, SDL_Surface* surface2, size_t x, size_t y, Uint32 color);

#endif
