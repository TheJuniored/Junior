#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "err.h"
#include "string.h"

int flood_fill(SDL_Surface* surface, int x, int y) {
    int res = 0;
    Uint32* pixels = surface->pixels;
    if (x < surface->w && y < surface->h){
        if (pixels[x + y * surface->w] == SDL_MapRGB(surface->format, 255, 255, 255)) {
            res++;
            pixels[x + y * surface->w] = SDL_MapRGB(surface->format, 0, 255, 0);
            res += flood_fill(surface, x - 1, y);
            res += flood_fill(surface, x + 1, y);
            res += flood_fill(surface, x, y - 1);
            res += flood_fill(surface, x, y + 1);
        }
    }
    return res;
}

SDL_Surface *load_image(char *filename)
{
    SDL_Surface* loadedImage = IMG_Load(filename);
    if (loadedImage == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Surface* optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGBA8888, 0);
    if (optimizedImage == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}

int main(int argc, char** argv) {
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: %s image", argv[0]);
    SDL_Surface* surface = load_image(argv[1]);
    SDL_Surface* cpy = NULL;
    memcpy(cpy, surface, sizeof(SDL_Surface));
    int x = 0;
    int y = 0;
    int mini = 0;


    flood_fill(surface, x, y);
    IMG_SavePNG(surface, "blob.png");
    SDL_FreeSurface(cpy);
    SDL_FreeSurface(surface);
    return EXIT_SUCCESS;
}






