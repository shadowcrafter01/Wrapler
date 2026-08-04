#ifndef ENG_INPUT_CPP
#define ENG_INPUT_CPP

#include <SDL3/SDL.h>
#include <Vector2.hpp>

class ENG_Input
{
private:
    class Mouse
    {
    private:
    public:
        Mouse();
        inline static Vector2<float> pos = Vector2<float>(0, 0);
        inline static void buttonDown(SDL_Event *event)
        {
            switch (event->button.button)
            {
            case SDL_BUTTON_RIGHT:
                clickR = true;
                holdR = true;
                break;
            case SDL_BUTTON_LEFT:
                clickL = true;
                holdL = true;
                break;
            case SDL_BUTTON_MIDDLE:
                clickM = true;
                holdM = true;
                break;

            default:
                break;
            }
        }
        inline static void buttonUp(SDL_Event *event)
        {
            switch (event->button.button)
            {
            case SDL_BUTTON_RIGHT:
                holdR = false;
                break;
            case SDL_BUTTON_LEFT:
                holdL = false;
                break;
            case SDL_BUTTON_MIDDLE:
                holdM = false;
                break;
            default:
                break;
            }
        }
        inline static void resetClick()
        {
            clickR = false;
            clickM = false;
            clickL = false;
        }

        //        inline static Vector2<double> worldPos(ENG_Camera *camera)
        //        {
        //            Vector2<double> out = pos;
        //
        //            out.x -= camera->window->center.x;
        //            out.y -= camera->window->center.y;
        //
        //            out.y *= -1;
        //
        //            out.rotate(-camera->angle);
        //
        //            out /= camera->zoom;
        //
        //            out.x += camera->position.x;
        //            out.y += camera->position.y;
        //
        //            return out;
        //        }

        inline static bool clickR;
        inline static bool clickM;
        inline static bool clickL;

        inline static bool holdR;
        inline static bool holdM;
        inline static bool holdL;
    };

public:
    ENG_Input();
    inline static void Update()
    {
        SDL_GetMouseState(&Mouse::pos.x, &Mouse::pos.y);
    }
    inline static void MouseDown()
    {
    }

    //inline static Mouse mouse = Mouse();

    class Keyboard
    {
    private:
    public:
        Keyboard();
    };
};

#endif