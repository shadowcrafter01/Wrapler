#include "init.hpp"
#include <SDL3/SDL_main.h>

#include "game.hpp"



void onMouseClick();
void onMouseClick2();
void onMouseClick3();

int main(int argc, char *argv[])
{
    ENG::Init();

    WIN::primary.SetIcon("data/textures/billGates.bmp");

    ENG::console.LogInfo("test");
    ENG::console.LogDebug(ENG::timer.now_ns());

    TTF_Text *testtext = FNT::sonic2.MakeText("test", &WIN::primary);
    TTF_Text *cutest = FNT::cu.MakeText("let's not give up just yet", &WIN::primary);

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

        mainTick();
        TTF_DrawRendererText(testtext, 0, 0);
        TTF_DrawRendererText(cutest, 0, 20);

        if (ENG::input.GetMouseState(SDL_BUTTON_LEFT))
        {
            ENG::console.LogInfo("ooga booga");
        }

        // TTF_DrawRendererText(FNT::cu.MakeText(std::to_string(ENG::timer.FPS),&WIN::primary),ENG::input.getMousePos().x,ENG::input.getMousePos().y);
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