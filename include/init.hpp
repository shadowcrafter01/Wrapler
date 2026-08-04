#ifndef INIT_HPP
#define INIT_HPP

#include "ENG_Main.hpp"

// static SDL_Window *window = NULL;
struct ENG_Windows
{
    ENG_Window prime = ENG::CreateWindow("le wrapler rawr", Vector2(640, 480), SDL_WINDOW_RESIZABLE);
};
extern ENG_Windows WIN;

struct ENG_Fonts
{
    ENG_Font sonic2 = ENG::CreateFont("data/fonts/sonic-hud-c-italic.ttf", 12);
    ENG_Font cu = ENG::CreateFont("data/fonts/Retro.Gaming.Extended.ttf", 24);
};
extern ENG_Fonts FNT;

struct ENG_Textures
{
    ENG_Texture billGates = ENG::CreateTexture("data/textures/billGates.bmp", &WIN.prime);
};
extern ENG_Textures TEX;

struct ENG_Sounds
{
    ENG_Audio boom = ENG::CreateAudio("data/sounds/vine-boom.mp3");
};
extern ENG_Sounds AUD;

static float mouseX;
static float mouseY;
static Uint64 last_check;

#include "ENG_Timer.hpp"

#endif