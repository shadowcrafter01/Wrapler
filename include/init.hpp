#ifndef INIT_HPP
#define INIT_HPP

#include "ENG_Main.hpp"

struct WIN
{
    inline static ENG_Window primary = ENG::CreateWindow("le wrapler rawr", Vector2(640, 480), SDL_WINDOW_RESIZABLE);
    inline static ENG_Window test = ENG::CreateWindow("test", Vector2(640, 480), SDL_WINDOW_RESIZABLE);
};

struct FNT
{
    inline static ENG_Font sonic2 = ENG::CreateFont("data/fonts/sonic-hud-c-italic.ttf", 12);
    inline static ENG_Font cu = ENG::CreateFont("data/fonts/Retro.Gaming.Extended.ttf", 24);
};

struct CAM
{
    inline static ENG_Camera primary = ENG::CreateCamera(&WIN::primary);
    inline static ENG_Camera test = ENG::CreateCamera(&WIN::test);
};

struct TEX
{ // each texture has to be attached to a specific window
    inline static ENG_Texture billGates = ENG::CreateTexture(&WIN::primary, "data/textures/billGates.bmp");
    inline static ENG_Texture test = ENG::CreateTexture(&WIN::test, "data/textures/billGates.bmp");
};

struct AUD
{
    inline static ENG_Audio boom = ENG::CreateAudio("data/sounds/vine-boom.mp3");
    inline static ENG_Audio boom2 = ENG::CreateAudio("data/sounds/vine-boom.mp3");
};

struct JSON
{
    inline static ENG_File test = ENG::CreateFile("test_file.json");
};

#include "ENG_Timer.hpp"

#endif