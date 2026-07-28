#ifndef ENG_TEXTURE_HPP
#define ENG_TEXTURE_HPP

#include "ENG_Window.hpp"
#include "Vector2.hpp"

class ENG_Texture
{
private:
public:
    ENG_Texture(const char *path, ENG_Window *window) : path{path}
    {
        surface = SDL_LoadBMP(path);
        width = surface->w;
        height = surface->h;
        pointer = SDL_CreateTextureFromSurface(window->renderer.pointer, surface);
    }
    int width;
    int height;
    const char *path;
    SDL_Texture *pointer;
    SDL_Surface *surface;
};

#endif