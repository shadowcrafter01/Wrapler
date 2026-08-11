#include "init.hpp"
#include <SDL3/SDL_main.h>

#include "game.hpp"

void onMouseClick();
void onMouseClick2();
void onMouseClick3();

int main(int argc, char *argv[])
{
    ENG::Init("Wrapler", "0.0", "com.wrapler.engine");

    WIN::primary.SetIcon("data/textures/billGates.bmp");

    ENG::console.LogInfo("test");
    ENG::console.LogDebug(ENG::timer.now_ns());

    ENG::input.RegisterMouseUp_R(onMouseClick);
    ENG::input.RegisterMouseDown_L(onMouseClick2);
    ENG::input.RegisterMouseDown_R(onMouseClick3);

    float test_number;
    bool test_bool;
    JSON::test.readProperty<float>("test_number", &test_number, 0);
    JSON::test.readProperty<bool>("test_bool", &test_bool, false);

    double averageFPS = 0;
    double averageFPS_old;
    double averageFPS_best;
    JSON::test.readProperty("average_fps",&averageFPS_old,0.0);
    JSON::test.readProperty("average_fps_best",&averageFPS_best,0.0);

    while (ENG::Update())
    {
        averageFPS = (0.999 * averageFPS) + ((1-0.999) * ENG::timer.FPS);
        controls();

        for (int i = 0; i <= 100; i++)
        {
            for (int j = 0; j <= 100; j++)
            {
                ENG::draw.DrawTexture(&TEX::billGates, Vector2(i * 100, j * 100), 1, ENG::timer.now_s() * 60);
            }
            ENG::draw.DrawFont(&CAM::primary, &FNT::cu, "test", Vector2(i * 100, -100));
        }
        ENG::draw.DrawTexture(&TEX::billGates, ENG::input.GetMouseWorldPos(&CAM::primary), 0.5);
        ENG::draw.DrawTexture(&TEX::test, ENG::input.GetMouseWorldPos(&CAM::test), 0.5);
        ENG::draw.DrawFont(&CAM::test, &FNT::cu, std::to_string(ENG::draw.textureDrawCount), WIN::test.size * Vector2(-0.5, 0.5));
        ENG::draw.DrawFont(&CAM::test, &FNT::cu, std::to_string(averageFPS), (WIN::test.size * Vector2(-0.5, 0.5)) + Vector2(0, -20));
        ENG::draw.DrawFont(&CAM::test, &FNT::cu, std::to_string(averageFPS_old), (WIN::test.size * Vector2(-0.5, 0.5)) + Vector2(0, -40));
        ENG::draw.DrawFont(&CAM::test, &FNT::cu, std::to_string(averageFPS_best), (WIN::test.size * Vector2(-0.5, 0.5)) + Vector2(0, -60));
    }
    JSON::test.writeProperty<double>("average_fps",averageFPS);

    if (averageFPS > averageFPS_best)
    {
        JSON::test.writeProperty<double>("average_fps_best",averageFPS);
    }

    ENG::Shutdown();
    return 0;
}

void onMouseClick()
{
    AUD::boom.Play();
}
void onMouseClick2()
{
    ENG::console.LogInfo("test");
}
void onMouseClick3()
{
    ENG::console.Log(std::to_string(ENG::timer.now_s()));
}