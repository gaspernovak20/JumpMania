#pragma once
#include "raylib.h"
#include <vector>

using namespace std;

class AudioManager
{
private:
    float sfxVolume = 1.0f;
    vector<Sound> sfxSounds;

public:
    AudioManager() {};
    void setSfxVolume(float v);
    void registerSfx(Sound &s);
    float getSoundVolume() { return sfxVolume; };
};
