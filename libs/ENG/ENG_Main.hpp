#ifndef ENG_MAIN_HPP
#define ENG_MAIN_HPP

#include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>

#include "Vector2.hpp"

#include "ENG_Window.hpp"
#include "ENG_Texture.hpp"

class ENG_Main
{
private:
    /* data */
public:
    ENG_Main(/* args */)
    {
    }

    bool Init()
    {
        // metadata
        if (!SDL_SetAppMetadata("Wrapler", "0.0", "com.wrapler.engine"))
        {
            return false;
        }

        // init sdl
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("SDL init error: %s", SDL_GetError());
            return false;
        }

        return true;
    }
};

#endif