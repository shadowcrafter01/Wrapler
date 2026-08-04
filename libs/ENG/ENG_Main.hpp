#ifndef ENG_MAIN_HPP
#define ENG_MAIN_HPP

#include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <iostream>
#include <functional>

#include "Vector2.hpp"

#include "ENG_Console.hpp"
#include "ENG_Window.hpp"
#include "ENG_Texture.hpp"
#include "ENG_Font.hpp"
#include "ENG_Timer.hpp"
#include "ENG_Audio.hpp"
#include "ENG_Input.hpp"

class ENG
{
private:
public:
    ENG(/* args */)
    {
    }

    inline static bool Init()
    {
        // metadata
        if (!SDL_SetAppMetadata("Wrapler", "0.0", "com.wrapler.engine"))
        {
            return false;
        }

        // init sdl
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("SDL init error: %s", SDL_GetError());
            return false;
        }

        GAMESTATE = true;
        return true;
    }

    inline static void Event()
    {
        SDL_Event ENG_Event;
        while (SDL_PollEvent(&ENG_Event))
        {
            switch (ENG_Event.type)
            {
            case SDL_EVENT_QUIT:
                GAMESTATE = false;
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                GAMESTATE = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                // keyboard down stuff here

                break;
            case SDL_EVENT_KEY_UP:
                // keyboard up stuff here

                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                // mouse down stuff here
                //ENG_Input::mouse.buttonDown(&ENG_Event);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                // mouse up stuff here
                //ENG_Input::mouse.buttonUp(&ENG_Event);
                break;
            default:
                break;
            }
        }
    }

    inline static bool Update()
    {
        Event();
        ENG_Window::UpdateAll();
        timer.update();
        ENG_Input::Update();

        return GAMESTATE;
    }

    inline static void Shutdown()
    {
        SDL_Quit();
    }

    inline static bool GAMESTATE = false;
    inline static ENG_Timer timer;
    inline static ENG_Console console = ENG_Console(&timer);
    //inline static ENG_Input input;

    inline static ENG_Window CreateWindow(const char *title, Vector2<int> size, SDL_WindowFlags flags)
    {
        return ENG_Window(title, size, flags);
    }
    inline static ENG_Texture CreateTexture(const char *path, ENG_Window* window)
    {
        return ENG_Texture(path, window);
    }
    inline static ENG_Font CreateFont(const char *path, int point)
    {
        return ENG_Font(path, point);
    }
    inline static ENG_Audio CreateAudio(const char *path)
    {
        return ENG_Audio(path);
    }
};


#endif