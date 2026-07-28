#define SDL_MAIN_USE_CALLBACKS 1

#include "init.hpp"
#include <SDL3/SDL_main.h> //i think this has to go in main.cpp very specifically for sdl3 to know where to start



#include "game.hpp"

// #define WINDOW_WIDTH 640
// #define WINDOW_HEIGHT 480



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{

    if (!engine.Init())
    {
        return SDL_APP_FAILURE;
    }

    // set window icon
    WIN.prime.SetIcon("data/textures/billGates.bmp");



    // fps font thing
    if (!TTF_Init())
    {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    font = TTF_OpenFont("data/fonts/sonic-hud-c-italic.ttf", 12);
    if (!font)
    {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    ttfengine = TTF_CreateRendererTextEngine(WIN.prime.renderer.pointer);
    if (!ttfengine)
    {
        SDL_Log("Couldn't create text engine: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    text = TTF_CreateText(ttfengine, font, "Calculating...", 0);
    if (!text)
    {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    TTF_SetTextColor(text, 255, 255, 255, SDL_ALPHA_OPAQUE);
    last_check = SDL_GetTicks();

    // what
    SDL_Log("what");

    // SDL_SetWindowShape(window, surface);
    // SDL_PropertiesID props = SDL_GetWindowProperties(window);
    // HWND hwnd = (HWND)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
    // LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    // SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    // SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
        // keyboard down stuff here
        break;
    case SDL_EVENT_KEY_UP:
        // keyboard up stuff here
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        // mouse down stuff here
        //MIX_PlayAudio(mixer, audio);
        AUD.boom.Play();
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        // mouse up stuff here
        break;
    default:
        break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    // main render loop (runs as fast as possible)
    SDL_SetRenderDrawColor(WIN.prime.renderer.pointer, 0, 0, 0, 0);
    SDL_RenderClear(WIN.prime.renderer.pointer);
    WIN.prime.Update();

    ENG_Timer.update();

    mainTick();

    SDL_RenderPresent(WIN.prime.renderer.pointer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // SDL_DestroyTexture(texture);
    //  end things
}