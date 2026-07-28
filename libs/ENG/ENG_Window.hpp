#ifndef ENG_WINDOW_HPP
#define ENG_WINDOW_HPP

#include <SDL3/SDL.h>
#include "Vector2.hpp"

class ENG_Window
{
private:
    struct ENG_Renderer
    {
        SDL_Renderer *pointer;
    };

public:
    ENG_Window(const char *title, Vector2<int> size, SDL_WindowFlags flags) : title{title},
                                                                              size{size},
                                                                              flags{flags}
    {
        if (!SDL_CreateWindowAndRenderer(title, size.x, size.y, flags, &pointer, &renderer.pointer))
        {
            // return SDL_APP_FAILURE;
        }
    }

    SDL_Window *pointer;
    ENG_Renderer renderer;

    const char *title;
    Vector2<int> size;
    SDL_WindowFlags flags;

    void SetIcon(const char *path)
    {
        SDL_Surface *surface = SDL_LoadBMP(path);
        int width = surface->w;
        int height = surface->h;
        if (!SDL_SetWindowIcon(pointer, surface))
        {
            SDL_Log("texture no exist: %s", SDL_GetError());
        }
    }
    void Update()
    {
        SDL_GetWindowSizeInPixels(pointer, &size.x, &size.y);
    }
};

#endif