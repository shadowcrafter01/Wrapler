#ifndef ENG_INPUT_CPP
#define ENG_INPUT_CPP

#include <SDL3/SDL.h>
#include <Vector2.hpp>
// #include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>

class ENG_Input
{
private:
    inline static std::unordered_set<SDL_Scancode> _keys;
    inline static std::unordered_set<SDL_Scancode> _keysPressed;
    inline static std::unordered_set<SDL_Scancode> _keysReleased;

    // mouse state
    inline static std::unordered_set<Uint8> _mouseButtons;
    inline static std::unordered_set<Uint8> _mousePressed;
    inline static std::unordered_set<Uint8> _mouseReleased;

    inline static float _mouseX = 0.0f;
    inline static float _mouseY = 0.0f;
    inline static float _mouseU = 0.0f;
    inline static float _mouseV = 0.0f;
    inline static float _wheelX = 0.0f;
    inline static float _wheelY = 0.0f;

    inline static std::vector<std::function<void()>> _mouseDownFunctionsR; // right click
    inline static std::vector<std::function<void()>> _mouseDownFunctionsM; // middle click
    inline static std::vector<std::function<void()>> _mouseDownFunctionsL; // left click

    inline static std::vector<std::function<void()>> _mouseUpFunctionsR; // right click
    inline static std::vector<std::function<void()>> _mouseUpFunctionsM; // middle click
    inline static std::vector<std::function<void()>> _mouseUpFunctionsL; // left click

public:
    static void Update(const SDL_Event &event)
    {
        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
            if (!event.key.repeat)
            {
                _keys.insert(event.key.scancode);
                _keysPressed.insert(event.key.scancode);
            }
            break;
        case SDL_EVENT_KEY_UP:
            _keys.erase(event.key.scancode);
            _keysReleased.insert(event.key.scancode);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            int w;
            int h;
            SDL_GetWindowSize(SDL_GetWindowFromID(event.window.windowID), &w, &h);
            _mouseX = SDL_clamp(event.motion.x, 0, w);
            _mouseY = SDL_clamp(event.motion.y, 0, h);
            _mouseU += event.motion.xrel;
            _mouseV += event.motion.yrel;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            _mouseButtons.insert(event.button.button);
            _mousePressed.insert(event.button.button);

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                for (std::function<void()> &func : _mouseDownFunctionsL)
                {
                    func();
                }
                break;
            case SDL_BUTTON_RIGHT:
                for (std::function<void()> &func : _mouseDownFunctionsR)
                {
                    func();
                }
                break;
            case SDL_BUTTON_MIDDLE:
                for (std::function<void()> &func : _mouseDownFunctionsM)
                {
                    func();
                }
                break;

            default:
                break;
            }

            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            _mouseButtons.erase(event.button.button);
            _mouseReleased.insert(event.button.button);

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                for (std::function<void()> &func : _mouseUpFunctionsL)
                {
                    func();
                }
                break;
            case SDL_BUTTON_RIGHT:
                for (std::function<void()> &func : _mouseUpFunctionsR)
                {
                    func();
                }
                break;
            case SDL_BUTTON_MIDDLE:
                for (std::function<void()> &func : _mouseUpFunctionsM)
                {
                    func();
                }
                break;

            default:
                break;
            }

            break;
        case SDL_EVENT_MOUSE_WHEEL:
            _wheelX += event.wheel.x;
            _wheelY += event.wheel.y;
            break;

        default:
            break;
        }
    }

    // register functions to mouse inputs
    inline static void RegisterMouseDown_R(std::function<void()> function)
    {
        _mouseDownFunctionsR.push_back(function);
    }
    inline static void RegisterMouseDown_L(std::function<void()> function)
    {
        _mouseDownFunctionsL.push_back(function);
    }
    inline static void RegisterMouseDown_M(std::function<void()> function)
    {
        _mouseDownFunctionsM.push_back(function);
    }
    inline static void RegisterMouseUp_R(std::function<void()> function)
    {
        _mouseUpFunctionsR.push_back(function);
    }
    inline static void RegisterMouseUp_L(std::function<void()> function)
    {
        _mouseUpFunctionsL.push_back(function);
    }
    inline static void RegisterMouseUp_M(std::function<void()> function)
    {
        _mouseUpFunctionsM.push_back(function);
    }

    // raw mouse state (for getting inputs from random buttons besides R L or M)
    static bool GetMouseInput(Uint8 button)
    {
        return _mousePressed.count(button) != 0;
    }

    // keyboard stuf
    static bool keyDown(SDL_Scancode sc)
    {
        return _keysPressed.count(sc) != 0;
    }
    static bool keyUp(SDL_Scancode sc)
    {
        return _keysReleased.count(sc) != 0;
    }
    static bool keyState(SDL_Scancode sc)
    {
        return _keys.count(sc) != 0;
    }

    static Vector2<float> getMousePos()
    {
        return Vector2<float>(_mouseX, _mouseY);
    }
    static Vector2<float> getMouseVel()
    {
        return Vector2<float>(_mouseU, _mouseV);
    }
};

#endif