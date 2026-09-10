#include "init.hpp"
#include <SDL3/SDL_main.h>
#include <Windows.h>
#include <Psapi.h>

#include "game.hpp"

#include <random>
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

GameObject test;

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

    //ENG::input.RegisterMouseUp_R(onMouseUpR);
    //ENG::input.RegisterMouseDown_L(onMouseDownL);

    float test_number;
    bool test_bool;
    JSON::test.readProperty<float>("test_number", &test_number, 0);
    JSON::test.readProperty<bool>("test_bool", &test_bool, false);

    double averageFPS = 0;
    double averageFPS_old;
    double averageFPS_best;
    JSON::test.readProperty("average_fps", &averageFPS_old, 0.0);
    JSON::test.readProperty("average_fps_best", &averageFPS_best, 0.0);

    test.AssignCamera(&CAM::primary);
    test.AssignTexture(&TEX::test);
    test.AssignTimer(&ENG::timer);
    test.damping = 0.5;
    test.fenceToWindow = true;
    test.AssignClickEvent_L(&onMouseDownL);
    test.position = {100,0};

    ENG_CollisionShape tempShape;
    tempShape.radius = 20;
    test.AssignCollisionShape(&tempShape);

    //ENG_CollisionShape temp;
    //test.collisionShape = &temp;

    ENG_Pen testPen = ENG_Pen(&CAM::primary);

    ENG_Atlas atlas(&WIN::primary,"data/textures/billGates.bmp");
    atlas.rect.x = 0;
    atlas.rect.y = 0;
    atlas.rect.w = 64;
    atlas.rect.h = 64;

    while (ENG::Update())
    {
        averageFPS = ENG_Math::Lerp(averageFPS, ENG::timer.FPS, 0.1);
        mainTick();
        controls();

        ENG::draw.DrawAtlas(&CAM::primary, &atlas, {0,0});
        atlas.rect.x = ENG::input.GetMouseWorldPos(&CAM::primary).x/10;//10 * cos(ENG::timer.now_s() * 15);
        atlas.rect.y = ENG::input.GetMouseWorldPos(&CAM::primary).y/10;//10 * sin(ENG::timer.now_s() * 15);


        //test.ApplyForce((ENG::input.GetMouseWorldPos(&CAM::primary, true) - test.position).Scale(1, true));

        // ENG::draw.DrawLine(&CAM::primary,{0,0},ENG::input.GetMouseWorldPos(&CAM::primary));
        // ENG::draw.DrawTri(&CAM::primary,{-100,-100},{100,-100},ENG::input.GetMouseWorldPos(&CAM::primary),colorRGBA(128,10,200,255));

        // testPen.GoTo({0,0});
        // testPen.Down();
        // testPen.GoTo({100,100});
        // testPen.GoTo(ENG::input.GetMouseWorldPos(&CAM::primary));
        // testPen.GoTo({-100,0});
        // testPen.Up();

        if (ENG::input.keyState(SDL_SCANCODE_SPACE))
        {
            SDL_Delay(100);//(dist(rng));
        }
    }

    JSON::test.writeProperty<double>("average_fps", averageFPS);

    if (averageFPS > averageFPS_best)
    {
        JSON::test.writeProperty<double>("average_fps_best", averageFPS);
    }

    ENG::Shutdown();
    return 0;
}
