#define SDL_MAIN_USE_CALLBACKS 1

#include "init.hpp"
#include <SDL3/SDL_main.h> //i think this has to go in main.cpp very specifically for sdl3 to know where to start

#include "Timer.hpp"

// #define WINDOW_WIDTH 640
// #define WINDOW_HEIGHT 480

ENG_Main engine;
Timer ENG_Timer;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{

    if (!engine.Init())
    {
        return SDL_APP_FAILURE;
    }

    // load texture
    SDL_Surface *surface = SDL_LoadBMP("data/textures/billGates.bmp");
    texture_width = surface->w;
    texture_height = surface->h;
    texture = SDL_CreateTextureFromSurface(WIN.prime.renderer.pointer, surface);

    // set window icon
    WIN.prime.SetIcon("data/textures/billGates.bmp");
    // if (!SDL_SetWindowIcon(window.renderer->pointer, surface))
    //{
    //     SDL_Log("texture no exist: %s", SDL_GetError());
    // }

    // init audio system
    if (!MIX_Init())
    {
        SDL_Log("Couldn't init SDL_mixer library: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!mixer)
    {
        SDL_Log("Couldn't create mixer on default device: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // load audio
    audio = MIX_LoadAudio(mixer, "data/sounds/vine-boom.mp3", false);
    if (!audio)
    {
        SDL_Log("Couldn't load audio", SDL_GetError());
        return SDL_APP_FAILURE;
    }

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
        MIX_PlayAudio(mixer, audio);
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

    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_FRect rect;
    rect.x = mouseX;
    rect.y = mouseY;
    rect.h = texture_height;
    rect.w = texture_width;
    SDL_RenderTexture(WIN.prime.renderer.pointer, texture, NULL, &rect);

    /* Draw a single triangle with a different color at each vertex. Center this one and make it grow and shrink. */
    /* You always draw triangles with this, but you can string triangles together to form polygons. */
    SDL_Vertex vertices[4];
    const float size = 200.0f;
    SDL_zeroa(vertices);
    vertices[0].position.x = mouseX; //((float) WINDOW_WIDTH) / 2.0f;
    vertices[0].position.y = mouseY; //(((float) WINDOW_HEIGHT) - size) / 2.0f;
    vertices[0].color.r = 1.0f;
    vertices[0].color.a = 1.0f;
    vertices[1].position.x = ((WIN.prime.size.x) + size) / 2.0f;
    vertices[1].position.y = ((WIN.prime.size.y) + size) / 2.0f;
    vertices[1].color.g = 1.0f;
    vertices[1].color.a = 1.0f;
    vertices[2].position.x = ((WIN.prime.size.x) - size) / 2.0f;
    vertices[2].position.y = ((WIN.prime.size.y) + size) / 2.0f;
    vertices[2].color.b = 1.0f;
    vertices[2].color.a = 1.0f;
    SDL_RenderGeometry(WIN.prime.renderer.pointer, NULL, vertices, 3, NULL, 0);

    int w = 0, h = 0;
    int text_w = 0, text_h = 0;
    float x, y;
    Uint64 now = SDL_GetTicks();
    if ((now - last_check) >= 100)
    {
        char string[6];
        // float fps = frames * 1000.0f / (now - last_check);
        SDL_snprintf(string, sizeof(string), "%.2f", ENG_Timer.FPS); // fps);
        TTF_SetTextString(text, string, 0);

        /* Reset our counters for the next cycle */
        last_check = now;
        // frames = 0;
    }
    SDL_GetRenderOutputSize(WIN.prime.renderer.pointer, &w, &h);
    TTF_GetTextSize(text, &text_w, &text_h);
    x = (float)(w - text_w) / 2;
    y = (float)(h - text_h) / 2;
    TTF_DrawRendererText(text, x, y);

    // SDL_Delay(16);
    //++frames;

    SDL_RenderPresent(WIN.prime.renderer.pointer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // SDL_DestroyTexture(texture);
    //  end things
}