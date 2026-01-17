#pragma once
#include "raylib.h"
#include <vector>

using namespace std;

class AudioManager
{
private:
    float sfxVolume = 1.0f;
    vector<Sound> sfxSounds;
    Music music;

public:
    AudioManager() {};
    void Initial();
    void Update();
    void changeSoundState();
    void changeMusicState();
    void setSfxVolume(float v);
    void registerSfx(Sound &s);
    float getSoundVolume() { return sfxVolume; };
    bool isMusicPlaying() { return IsMusicStreamPlaying(music); }
};
