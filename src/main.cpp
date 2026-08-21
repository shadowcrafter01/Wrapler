#include "init.hpp"
#include <SDL3/SDL_main.h>
#include <Windows.h>
#include <Psapi.h>

#include "game.hpp"

#include <random>
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, 500);

//GameObject test;

void onMouseUpR()
{
    // AUD::boom.Play();
}
void onMouseDownL()
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    ENG::console.LogDebug(pmc.WorkingSetSize / 1024);
}

int main(int argc, char *argv[])
{
    ENG::Init("Wrapler", "0.0", "com.wrapler.engine");

    WIN::primary.SetIcon("data/textures/billGates.bmp");

    ENG::console.LogInfo("test");
    ENG::console.LogDebug(ENG::timer.now_ns());

    ENG::input.RegisterMouseUp_R(onMouseUpR);
    ENG::input.RegisterMouseDown_L(onMouseDownL);

    float test_number;
    bool test_bool;
    JSON::test.readProperty<float>("test_number", &test_number, 0);
    JSON::test.readProperty<bool>("test_bool", &test_bool, false);

    double averageFPS = 0;
    double averageFPS_old;
    double averageFPS_best;
    JSON::test.readProperty("average_fps", &averageFPS_old, 0.0);
    JSON::test.readProperty("average_fps_best", &averageFPS_best, 0.0);

    //test.AssignCamera(&CAM::primary);
    //test.AssignTexture(&TEX::billGates);
    //test.AssignTimer(&ENG::timer);
    //test.damping = 0.5;
    //test.fenceToWindow = true;

    while (ENG::Update())
    {
        averageFPS = (0.9 * averageFPS) + ((1 - 0.9) * ENG::timer.FPS);
        controls();

        //test.ApplyForce((ENG::input.GetMouseWorldPos(&CAM::primary, true) - test.position).Scale(1, true));
        //test.ApplyForce(test.velocity.Scale(-0.5, true));

        //ENG::draw.DrawLine(&CAM::primary,{0,0},ENG::input.GetMouseWorldPos(&CAM::primary));
        ENG::draw.DrawTri(&CAM::primary,{-100,-100},{100,-100},ENG::input.GetMouseWorldPos(&CAM::primary),colorRGBA(128,10,200,255));

        if (ENG::input.keyState(SDL_SCANCODE_SPACE))
        {
            SDL_Delay(dist(rng));
        }
        SDL_Delay(20);
    }

    JSON::test.writeProperty<double>("average_fps", averageFPS);

    if (averageFPS > averageFPS_best)
    {
        JSON::test.writeProperty<double>("average_fps_best", averageFPS);
    }

    ENG::Shutdown();
    return 0;
}
