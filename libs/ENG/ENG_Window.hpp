#ifndef ENG_WINDOW_HPP
#define ENG_WINDOW_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Vector2.hpp"
#include <vector>

class ENG_Window
{
private:
    struct ENG_Renderer
    {
        SDL_Renderer *pointer;
        operator SDL_Renderer *() const
        {
            return pointer;
        }
    };

    static std::vector<ENG_Window *> &instances()
    {
        static std::vector<ENG_Window *> v;
        return v;
    }

    //static std::vector<ENG_Window*> &instances;

public:
    ENG_Window(const char *title, Vector2<int> size, SDL_WindowFlags flags) : title{title},
                                                                              size{size},
                                                                              flags{flags}
    {
        if (!SDL_CreateWindowAndRenderer(title, size.x, size.y, flags, &pointer, &renderer.pointer))
        {
            // return SDL_APP_FAILURE;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        ttfEngine = TTF_CreateRendererTextEngine(renderer);
        instances().push_back(this);
    }
    ~ENG_Window()
    {
        //std::vector<ENG_Window*> &v = instances();
        if (renderer.pointer) SDL_DestroyRenderer(renderer);
        if (pointer) SDL_DestroyWindow(pointer);
    }

    //ENG_Window(const ENG_Window&) = delete;
    //ENG_Window& operator=(const ENG_Window&) = delete;

    SDL_Window *pointer;
    ENG_Renderer renderer;
    TTF_TextEngine *ttfEngine;

    const char *title;
    Vector2<int> size;
    Vector2<int> center;
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
        center=Vector2<int>(size.x/2,size.y/2);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    static void UpdateAll()
    {
        for (ENG_Window *w : instances())
        {
            w->Update();
        }
    }
};

#endif