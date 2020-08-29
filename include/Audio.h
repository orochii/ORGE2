#ifndef AUDIO_H
#define AUDIO_H

#define MUSIC_DEFAULT_FADE 200
#define AUDIO_CHANNELS 16

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Audio
{
    public:
        Audio();
        virtual ~Audio();
        void Init(int _numChannels);
        void Update();
        void Close();
        int GetBgmVolume();
        void SetBgmVolume(int v);
        int GetSfxVolume();
        void SetSfxVolume(int v);
        void PlaySound(Mix_Chunk* snd, int volume);
        void PlayMusic(Mix_Music* music, int volume, double position);
        void StopMusic();
    private:
        bool fading;
        int numChannels;
        int* channelsVolume = nullptr;
        int playingBgmVol = 0;
        int bgmVolume = 9;
        int sfxVolume = 9;
        Mix_Music* currentMusic = nullptr;
        void OnLoopMusic();
};

#endif // AUDIO_H
