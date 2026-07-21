#ifndef INIT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <Windows.h>

#include <iostream>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static int texture_width = 0;
static int texture_height = 0;
static float mouseX;
static float mouseY;
static MIX_Mixer *mixer = NULL;
static MIX_Audio *audio = NULL;
static MIX_Track *track = NULL;
static TTF_Font *font = NULL;
static TTF_TextEngine *engine = NULL;
static TTF_Text *text = NULL;
static int frames;
static Uint64 last_check;

#endif