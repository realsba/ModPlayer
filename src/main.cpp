#include <SDL2/SDL.h>
#include "SDL2/SDL_audio.h"

#include <csignal>

#include "Module.hpp"

constexpr int MIXER_FREQUENCY = 44100;

Module module(MIXER_FREQUENCY);

void audio_callback(void* userdata, Uint8* stream, int length)
{
    auto buffer = reinterpret_cast<Sint16*>(stream);
    length /= 2;
    for (int i = 0; i < length; ++i) {
        *buffer++ = module.getFrame();
    }
}

volatile int keepRunning = 1;

void handle_sigint(int sig)
{
    keepRunning = 0;
}

int main(int argc, char** argv)
{
    module.load(argv[1]);
    SDL_AudioSpec fmt;

    fmt.freq     = MIXER_FREQUENCY;
    fmt.format   = AUDIO_S16;
    fmt.channels = 1;
    fmt.samples  = 512;
    fmt.callback = audio_callback;
    fmt.userdata = nullptr;

    if (SDL_OpenAudio(&fmt, nullptr) < 0) {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }

    signal(SIGINT, handle_sigint);

    SDL_PauseAudio(0);

    while (keepRunning) {
        SDL_Delay(2000);
    }

    SDL_CloseAudio();
}
