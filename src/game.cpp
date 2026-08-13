#include "init.hpp"

void mainTick()
{


}

void controls()
{
    //if (ENG::input.GetMouseState(SDL_BUTTON_LEFT))
    //{
    //    ENG::console.LogInfo("ooga booga");
    //}

    if (ENG::input.keyState(SDL_SCANCODE_W))
    {
        //CAM::primary.position.y += 100 / CAM::primary.zoom * ENG::timer.delta;
        CAM::primary.position += Vector2<double>(0,200).Rotate(CAM::primary.angle) / CAM::primary.zoom * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_A))
    {
        //CAM::primary.position.x -= 100 / CAM::primary.zoom * ENG::timer.delta;
        CAM::primary.position += Vector2<double>(-200,0).Rotate(CAM::primary.angle) / CAM::primary.zoom * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_S))
    {
        //CAM::primary.position.y -= 100 / CAM::primary.zoom * ENG::timer.delta;
        CAM::primary.position += Vector2<double>(0,-200).Rotate(CAM::primary.angle) / CAM::primary.zoom * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_D))
    {
        //CAM::primary.position.x += 100 / CAM::primary.zoom * ENG::timer.delta;
        CAM::primary.position += Vector2<double>(200,0).Rotate(CAM::primary.angle) / CAM::primary.zoom * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_UP))
    {
        CAM::primary.zoom += 1 * CAM::primary.zoom * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_DOWN))
    {
        CAM::primary.zoom -= 1 * CAM::primary.zoom * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_LEFT))
    {
        CAM::primary.angle += 30 * ENG::timer.delta;
    }
    if (ENG::input.keyState(SDL_SCANCODE_RIGHT))
    {
        CAM::primary.angle -= 30 * ENG::timer.delta;
    }
}