#ifndef INIT_HPP
#define INIT_HPP

#include "ENG_Main.hpp"

// static SDL_Window *window = NULL;
struct ENG_Windows
{
    ENG_Windows() : prime("le wrapler rawr", Vector2(640, 480), SDL_WINDOW_RESIZABLE) //,vector2D(1920,1080)),

    {
    }
    ENG_Window prime;
};
extern ENG_Windows WIN;

// static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static int texture_width = 0;
static int texture_height = 0;
static float mouseX;
static float mouseY;
static MIX_Mixer *mixer = NULL;
static MIX_Audio *audio = NULL;
static MIX_Track *track = NULL;
static TTF_Font *font = NULL;
static TTF_TextEngine *ttfengine = NULL;
static TTF_Text *text = NULL;
// static int frames;
static Uint64 last_check;

#endif