#ifndef ENG_AUDIO_HPP
#define ENG_AUDIO_HPP

#include <SDL3_mixer/SDL_mixer.h>

// #include "ENG_Main.hpp"
#include "ENG_Console.hpp"

class ENG_Audio
{
private:
    void InitMixer()
    {
        if (!MIX_Init())
        {
            SDL_Log("Couldn't init SDL_mixer library: %s", SDL_GetError());
            // return false;
        }
        mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
        if (!mixer)
        {
            SDL_Log("Couldn't create mixer on default device: %s", SDL_GetError());
            // return false;
        }
    }
    static inline MIX_Mixer *mixer;
    static inline bool mixer_init = false;
public:
    ENG_Audio(const char *path)
    {
        if (!mixer_init)
        {
            InitMixer();
        }
        audio = MIX_LoadAudio(mixer, path, false);
        if (!audio)
        {
        }
    }

    void Play()
    {
        if (!MIX_PlayAudio(mixer, audio))
        {
            ENG_Console::LogError("Play Audio Fail");
        }
    }

    MIX_Audio *audio;
};

#endif