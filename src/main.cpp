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

    // TTF_Text *testtext = FNT::sonic2.MakeText("test", &WIN::primary);
    TTF_Text *test = FNT::cu.MakeText("let's not give up just yet", &WIN::primary);
    // TTF_Text *fps = FNT::cu.MakeText(std::to_string(ENG::timer.FPS),&WIN::primary);

    ENG::input.RegisterMouseUp_R(onMouseClick);
    ENG::input.RegisterMouseDown_L(onMouseClick2);
    ENG::input.RegisterMouseDown_R(onMouseClick3);

    ENG_File filetest = ENG_File("test_file.json");
    float test_number;
    bool test_bool;
    filetest.readProperty("test_number", &test_number, 0.0f);
    filetest.readProperty("test_bool", &test_bool, false);

    while (ENG::Update())
    {

        // mainTick();
        controls();

        

        for (int i = 0; i <= 100; i++)
        {
            for (int j = 0; j <= 100; j++)
            {
                ENG::draw.DrawTexture(&CAM::primary, &TEX::billGates, Vector2(i * 100, j * 100), 1, ENG::timer.now_s() * 60);
            }
            ENG::draw.DrawFont(&CAM::primary, &FNT::cu, "test", Vector2(i * 100, -100));
        }
        ENG::draw.DrawTexture(&CAM::primary, &TEX::billGates, ENG::input.GetMouseWorldPos(&CAM::primary), 0.5);
    }
    ENG::Shutdown();
    return 0;
}

void onMouseClick()
{
    // AUD.boom.Play();
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