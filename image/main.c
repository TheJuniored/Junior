//#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "err.h"

//charger l'image
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

//grayscle pixels
Uint32 pixel_to_grayscale(Uint32 pixel, SDL_PixelFormat *format)
{
    Uint8 r, g, b; 
    SDL_GetRGB(pixel, format, &r, &g, &b);
    Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b; 
    r = g = b = average;
    Uint32 gray = SDL_MapRGB(format, r, g, b); 
    return gray;
}

//grayscale surface
void surface_to_grayscale(SDL_Surface *surface)
{
    Uint32 *pixels = surface->pixels;
    int length = surface->w * surface->h;
    SDL_PixelFormat *format = surface->format;
    SDL_LockSurface(surface);
    for (int i = 0; i < length; i++)
        pixels[i] = pixel_to_grayscale(pixels[i], format);
    SDL_UnlockSurface(surface);
}

//thresholding
void adaptative_threshold(SDL_Surface *surface) {
    Uint32* copy = malloc(surface->w * surface->h * sizeof(Uint32));
    memcpy(copy, surface->pixels, surface->w * surface->h * sizeof(Uint32));
    Uint32 *pixels = surface->pixels;
    SDL_PixelFormat *format = surface->format; 
    SDL_LockSurface(surface);
    int range = 15;
    for (int i = 0; i < surface->h; i++) {
        for (int j = 0; j < surface->w; j++) {
            int sum = 0;
            for (int k = -range; k <= range; k++) {
                if (i + k < 0 || i + k >= surface->h)
                    continue;
                for (int l = -range; l <= range; l++) {
                    if (j + l < 0 || j + l >= surface->w)
                        continue;
                    Uint8 r, g, b;
                    SDL_GetRGB(copy[(i + k) * surface->w + (j + l)], format, &r, &g, &b);
                    sum += r;
                }
            }

            Uint8 average = sum / (2 * range + 1) / (2 * range + 1); 
            Uint8 r, g, b;
            SDL_GetRGB(pixels[i * surface->w + j], format, &r, &g, &b);
            if (r < average)
                pixels[i * surface->w + j] = SDL_MapRGB(format, 0, 0, 0);
            else
                pixels[i * surface->w + j] = SDL_MapRGB(format, 255, 255, 255);
        }
    }
    SDL_UnlockSurface(surface);


void dilatation(SDL_Surface* surface) {
    Uint32* pixels = surface->pixels;
    for (int i = 0; i < surface->h; i++) {
        for (int j = 0; j < surface->w; j++) {
            if (pixels[i * surface->w + j] == SDL_MapRGB(surface->format, 0, 0, 0)) { 
                if (i - 1 >= 0)
                    pixels[(i - 1) * surface->w + j] = SDL_MapRGB(surface->format, 0, 0, 0);
                else if (i + 1 < surface->h)
                    pixels[(i + 1) * surface->w + j] = SDL_MapRGB(surface->format, 0, 0, 0);
                else if (j - 1 >= 0)
                    pixels[i * surface->w + (j - 1)] = SDL_MapRGB(surface->format, 0, 0, 0);
                else if (j + 1 < surface->w)
                    pixels[i * surface->w + (j + 1)] = SDL_MapRGB(surface->format, 0, 0, 0);
            }
        }
    }
}

//white and black
void invert(SDL_Surface* surface) {
    Uint32* pixels = surface->pixels;
    for (int i = 0; i < surface->h; i++) {
        for (int j = 0; j < surface->w; j++) {
            if (pixels[i * surface->w + j] == SDL_MapRGB(surface->format, 0, 0, 0)) 
                pixels[i * surface->w + j] = SDL_MapRGB(surface->format, 255, 255, 255);
            else
                pixels[i * surface->w + j] = SDL_MapRGB(surface->format, 0, 0, 0);
        }
    }
}

//flood
int flood_fill(SDL_Surface* surface, size_t x, size_t y, Uint32 color) {
    int res = 0;
    Uint32* pixels = surface->pixels;
    if (x < (size_t)surface->w && y < (size_t)surface->h){
        if (pixels[x + y * surface->w] == SDL_MapRGB(surface->format, 255, 255, 255)) {
            res++;
            pixels[x + y * surface->w] = SDL_MapRGB(surface->format, 0, 255, 0);
            res += flood_fill(surface, x - 1, y, color);
            res += flood_fill(surface, x + 1, y, color);
            res += flood_fill(surface, x, y - 1, color);
            res += flood_fill(surface, x, y + 1, color);
        }
    }
    return res;
}

//grid
void get_grid(SDL_Surface* surface1, SDL_Surface* surface2, size_t x, size_t y, Uint32 color) {
    Uint32* pixels1 = surface1->pixels;
    Uint32* pixels2 = surface2->pixels;
    if (x < (size_t)surface1->w && y < (size_t)surface1->h){
        if (pixels1[x + y * surface1->w] == SDL_MapRGB(surface1->format, 255, 255, 255)) { 
            pixels1[x + y * surface1->w] = SDL_MapRGB(surface1->format, 0, 255, 0);
            pixels2[x + y * surface2->w] = SDL_MapRGB(surface2->format, 0, 255, 0);
            get_grid(surface1, surface2, x - 1, y, color);
            get_grid(surface1, surface2, x + 1, y, color);
            get_grid(surface1, surface2, x, y - 1, color);
            get_grid(surface1, surface2, x, y + 1, color);
        }
    }
}



int main(int argc, char *argv[]) {
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: %s image", argv[0]);

    SDL_Surface *image = load_image(argv[1]);

    SDL_LockSurface(image);

    surface_to_grayscale(image);
    adaptative_threshold(image);
    invert(image);
    SDL_Surface* copy = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
    size_t x = 0;
    size_t y = 0;
    int mini = 0;
    int tmp = 0;
    for (size_t i = 0; i < (size_t)copy->h; i++) {
        for (size_t j = 0; j < (size_t)copy->w; j++) {
            tmp = flood_fill(copy, j, i, SDL_MapRGB(copy->format, 0, 255, 0));
            if (tmp > mini) {
                mini = tmp;
                x = j;
                y = i;
            }
        }
    }
    
    SDL_Surface* copy2 = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
    for (size_t i = 0; i < (size_t)(copy2->h * copy->w); i++)
        ((Uint32*)copy2->pixels)[i] = SDL_MapRGB(copy2->format, 0, 0, 0);
    get_grid(image, copy2, x, y, SDL_MapRGB(copy2->format, 0, 255, 0));
    
    SDL_UnlockSurface(image);
    IMG_SavePNG(copy2, "/Users/maxime/Desktop/sudoku-solver/image/output.png");
    SDL_FreeSurface(image);
    SDL_FreeSurface(copy);
    SDL_FreeSurface(copy2);
   
    SDL_Quit();
    return EXIT_SUCCESS;
}
