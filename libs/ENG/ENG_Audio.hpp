#ifndef ENG_AUDIO_HPP
#define ENG_AUDIO_HPP

#include <SDL3_mixer/SDL_mixer.h>

#include "ENG_Main.hpp"

class ENG_Audio
{
private:
public:
    ENG_Audio(const char *path)
    {

        audio = MIX_LoadAudio(engine.mixer, path, false);
        if (!audio)
        {
            SDL_Log("Couldn't load audio", SDL_GetError());
        }
    }

    void Play()
    {
        MIX_PlayAudio(engine.mixer, audio);
    }

    MIX_Audio *audio;
};

#endif