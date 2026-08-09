#ifndef ENG_TEXTURE_HPP
#define ENG_TEXTURE_HPP

#include "ENG_Window.hpp"
#include "Vector2.hpp"
#include "ENG_Console.hpp"
#include <SDL3_image/SDL_image.h>
#include "ENG_Font.hpp"

class ENG_Texture
{
private:
public:
    ENG_Texture(const char *path) : path{path}
    {
        if (!check())
        {
            return;
        }
        // surface = SDL_LoadBMP(path);
        // width = surface->w;
        // height = surface->h;
        // pointer = SDL_CreateTextureFromSurface(window->renderer.pointer, surface);
    }
    ENG_Texture(SDL_Surface *in) : surface{in},
                                   state{1},
                                   path{""},
                                   size{Vector2<int>(in->w, in->h)}
    {
    }

    int width;
    int height;
    const char *path;
    SDL_Texture *pointer;
    SDL_Surface *surface;
    int state = -1;
    Vector2<int> size;

    bool check()
    {
        ENG_Console::LogLoadStart((std::string) "Checking source file [" + path + "]");
        SDL_Surface *tmpSurface = IMG_Load(path);
        if (tmpSurface == NULL)
        {
            if (path == "" && surface != NULL)
            {
                state = 0;
                ENG_Console::LogLoadEnd(true, "Surface validated");
                return true;
            }
            state = -1;
            ENG_Console::LogLoadEnd(false, SDL_GetError());
            return false;
        }
        state = 0;
        size = Vector2<int>(tmpSurface->w, tmpSurface->h);
        ENG_Console::LogLoadEnd(true, "File validated");
        return true;
    }

    void grab()
    {
        ENG_Console::LogLoadStart((std::string) "Grabbing texture file [" + path + "]");
        if (state == 0)
        {
            surface = IMG_Load(path);
            state = 1;
            // SDL_QueryTexture(surface,NULL,NULL,&size.x,&size.y);
            size.x = surface->w;
            size.y = surface->h;
            ENG_Console::LogLoadEnd(true, std::to_string(size.x) + "x" + std::to_string(size.y));
            return;
        }
        if (state <= 1)
        {
            return;
        }
        ENG_Console::LogLoadEnd(false, (std::string) "Texture has an invalid state! [" + std::to_string(state) + "]");
        return;
    }

    void load(ENG_Window *window)
    {
        if (state == -1)
        {
            if (!check())
            {
                return;
            }
        }
        if (state == 0)
        {
            grab();
        }

        ENG_Console::LogLoadStart((std::string) "Loading texture file [" + path + "]");

        if (state == 1)
        {
            pointer = SDL_CreateTextureFromSurface(window->renderer, surface);
            if (pointer == NULL)
            {
                state = -1;
                ENG_Console::LogLoadEnd(false, (std::string) "Could not load texture [" + path + "]");
                return;
            }
            state = 2;
            ENG_Console::LogLoadEnd(true);
            return;
        }
        if (state == 2)
        {
            ENG_Console::LogLoadEnd(true, "Already loaded!");
            return;
        }
        ENG_Console::LogLoadEnd(false, (std::string) "Texture [" + std::to_string(state) + "] has an invalid state!");
        return;
    }

    void unload()
    {
        ENG_Console::LogLoadStart((std::string) "Unloading texture: " + path);
        SDL_DestroyTexture(pointer);
        if (state == -1)
        {
            ENG_Console::LogLoadEnd(false);
            return;
        }
        state = 0;
        ENG_Console::LogLoadEnd(true, "Unloaded texture");
    }
};

#endif