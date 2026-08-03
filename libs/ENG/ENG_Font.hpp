#ifndef ENG_FONT_HPP
#define ENG_FONT_HPP

#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "ENG_Console.hpp"
#include "ENG_Texture.hpp"

class ENG_Font
{
private:
    void InitTTF()
    {
        if (!TTF_Init())
        {
            SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        }
        // ttfengine = TTF_CreateRendererTextEngine(WIN.prime.renderer.pointer);
        // if (!ttfengine)
        //{
        //     SDL_Log("Couldn't create text engine: %s\n", SDL_GetError());
        // }
    }
    static inline bool ttf_init = false;

public:
    ENG_Font(std::string path, int point) : path{path},
                                            point{point}
    {
        if (!ttf_init)
        {
            InitTTF();
        }
        font = TTF_OpenFont(path.c_str(), point);
        if (!font)
        {
            ENG_Console::LogError("Could not open font: [" + path + "]");
        }
    }
    TTF_Text *MakeText(std::string text, ENG_Window *window)
    {
        TTF_Text *textOut = TTF_CreateText(window->ttfEngine, font, text.c_str(), 0);
        TTF_SetTextColor(textOut, 255, 255, 255, SDL_ALPHA_OPAQUE);
        return textOut;
    }
    TTF_Font *font;
    std::string path;
    int point;
};

#endif