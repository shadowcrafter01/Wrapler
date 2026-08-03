#ifndef INIT_HPP
#define INIT_HPP

#include "ENG_Main.hpp"

// static SDL_Window *window = NULL;
struct ENG_Windows
{
    ENG_Windows() : prime("le wrapler rawr", Vector2(640, 480), SDL_WINDOW_RESIZABLE)//,
                    //test("booger", Vector2(640, 480), SDL_WINDOW_RESIZABLE)
    {
    }
    ENG_Window prime;
    //ENG_Window test;
};
extern ENG_Windows WIN;

struct ENG_Fonts
{
    ENG_Fonts() : sonic2("data/fonts/sonic-hud-c-italic.ttf",12)
    {
    }
    ENG_Font sonic2;
};
extern ENG_Fonts FNT;

struct ENG_Textures
{
    ENG_Textures() : billGates("data/textures/billGates.bmp", &WIN.prime)
    {
    }
    ENG_Texture billGates;
};
extern ENG_Textures TEX;

struct ENG_Sounds
{
    ENG_Sounds() : boom("data/sounds/vine-boom.mp3")
    {
    }
    ENG_Audio boom;
};
extern ENG_Sounds AUD;

// static SDL_Renderer *renderer = NULL;
// static SDL_Texture *texture = NULL;
// static int texture_width = 0;
// static int texture_height = 0;
static float mouseX;
static float mouseY;
// static MIX_Mixer *mixer = NULL;
// static MIX_Audio *audio = NULL;
// static MIX_Track *track = NULL;
//static TTF_Font *font = NULL;
//static TTF_TextEngine *ttfengine = NULL;
//static TTF_Text *text = NULL;
// static int frames;
static Uint64 last_check;

#include "ENG_Timer.hpp"


#endif