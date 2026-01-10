#include "raylib.h"
#include "include/AudioManager.h"

void AudioManager::setSfxVolume(float v)
{
    sfxVolume = v;
    for (Sound &s : sfxSounds)
        SetSoundVolume(s, sfxVolume);
}

void AudioManager::registerSfx(Sound &s)
{
    sfxSounds.push_back(s);
    SetSoundVolume(s, sfxVolume);
}
