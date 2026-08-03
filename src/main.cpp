#include "init.hpp"
#include <SDL3/SDL_main.h>

#include "game.hpp"


int main(int argc, char *argv[])
{
    ENG_Main::Init();

    WIN.prime.SetIcon("data/textures/billGates.bmp");

    ENG_Console::LogInfo("test1");
    console.LogInfo("test2");
    ENG_Console::LogDebug(ENG_timer.now_ns());

    AUD.boom.Play();

    TTF_Text *testtext = FNT.sonic2.MakeText("test",&WIN.prime);

    while (ENG_Main::Update())
    {

        mainTick();
        TTF_DrawRendererText(testtext,0,0);

    }
    ENG_Main::Shutdown();
    return 0;
}


