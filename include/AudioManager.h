#pragma once
#include "raylib.h"
#include "./Settings.h"
#include <vector>

using namespace std;

class AudioManager
{
private:
    float sfxVolume = 1.0f;
    vector<Sound> sfxSounds;
    Music music;
    Settings &settings;

public:
    AudioManager(Settings &settings) : settings(settings) {};
    void Initial();
    void Update();
    void ApplySettings(const Settings &s);
    void changeSoundState();
    void changeMusicState();
    void registerSfx(Sound &s);
    void setSfxVolume(float v);
    float getSoundVolume() { return sfxVolume; };
    bool isMusicPlaying() { return IsMusicStreamPlaying(music); }
};
