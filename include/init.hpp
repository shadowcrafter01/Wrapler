#ifndef INIT_HPP
#define INIT_HPP

#include "ENG_Main.hpp"

struct WIN
{
    inline static ENG_Window primary = ENG::CreateWindow("le wrapler rawr", Vector2(640, 480), SDL_WINDOW_RESIZABLE);
};

struct FNT
{
    inline static ENG_Font sonic2 = ENG::CreateFont("data/fonts/sonic-hud-c-italic.ttf", 12);
    inline static ENG_Font cu = ENG::CreateFont("data/fonts/Retro.Gaming.Extended.ttf", 24);
};

struct TEX
{
    inline static ENG_Texture billGates = ENG::CreateTexture("data/textures/billGates.bmp", &WIN::primary);
};

struct CAM
{
    inline static ENG_Camera primary = ENG::CreateCamera(&WIN::primary);
};


struct AUD
{
    inline static ENG_Audio boom = ENG::CreateAudio("data/sounds/vine-boom.mp3");
    inline static ENG_Audio boom2 = ENG::CreateAudio("data/sounds/vine-boom.mp3");
};


#include "ENG_Timer.hpp"

#endif