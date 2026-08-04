#include "init.hpp"
#include <SDL3/SDL_main.h>

#include "game.hpp"


int main(int argc, char *argv[])
{
    ENG::Init();

    WIN.prime.SetIcon("data/textures/billGates.bmp");

    ENG::console.LogInfo("test");
    ENG::console.LogDebug(ENG::timer.now_ns());

    AUD.boom.Play();

    TTF_Text *testtext = FNT.sonic2.MakeText("test",&WIN.prime);
    TTF_Text *cutest = FNT.cu.MakeText("let's not give up just yet",&WIN.prime);

    while (ENG::Update())
    {

        mainTick();
        TTF_DrawRendererText(testtext,0,0);
        TTF_DrawRendererText(cutest,0,20);

        //if (ENG_Input::mouse.holdL)//ENG::input.mouse.holdL)
        //{
        //    AUD.boom.Play();
        //}

    }
    ENG::Shutdown();
    return 0;
}