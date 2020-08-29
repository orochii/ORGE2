#include "Audio.h"

#define MAX_VOLUME 10

Audio::Audio() {}

Audio::~Audio() {}

void Audio::Init(int _numChannels) {
    numChannels = _numChannels;
    //std::cout << "Allocated channels: " << numChannels << std::endl;
    channelsVolume = new int[numChannels];
}

void Audio::Update() {
    if (!Mix_PlayingMusic()) {
        OnLoopMusic();
    }
}

void Audio::Close() {
    StopMusic();
    delete [] channelsVolume;
    channelsVolume = nullptr;
}

int Audio::GetBgmVolume() {
    return bgmVolume;
}

void Audio::SetBgmVolume(int v) {
    bgmVolume = v;
    Mix_VolumeMusic((bgmVolume * playingBgmVol) / MAX_VOLUME);
}

int Audio::GetSfxVolume() {
    return sfxVolume;
}

void Audio::SetSfxVolume(int v) {
    sfxVolume = v;
    for (int i = 0; i < numChannels; i++) {
        Mix_Volume(i, (sfxVolume * channelsVolume[i]) / MAX_VOLUME);
    }
}

void Audio::PlaySound(Mix_Chunk* snd, int volume) {
    int chnl = Mix_PlayChannel(-1, snd, 0);
    channelsVolume[chnl] = volume;
    //Mix_Volume(chnl, (sfxVolume * volume) / MAX_VOLUME);
}

void Audio::PlayMusic(Mix_Music* music, int volume, double position) {
    playingBgmVol = volume;
    if (currentMusic == music) return;
    if (currentMusic == nullptr) {
        currentMusic = music;
        Mix_PlayMusic(currentMusic, 0);
        Mix_VolumeMusic((bgmVolume * playingBgmVol) / MAX_VOLUME);
        Mix_SetMusicPosition(position);
    } else {
        Mix_FadeOutMusic(MUSIC_DEFAULT_FADE);
        currentMusic = music;
    }
}

void Audio::StopMusic() {
    currentMusic = nullptr;
    Mix_HaltMusic();
}

void Audio::OnLoopMusic() {
    if (currentMusic != nullptr) {
        Mix_PlayMusic(currentMusic, 0);
        Mix_VolumeMusic((bgmVolume * playingBgmVol) / MAX_VOLUME);
        if (!fading) {
            // TODO: Set loop position.
        }
        fading = false;
    }
}
