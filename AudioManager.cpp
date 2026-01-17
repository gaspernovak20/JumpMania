#include "raylib.h"
#include "include/AudioManager.h"
#include "include/Settings.h"

void AudioManager::Initial()
{
    music = LoadMusicStream("../assets/sound/music.mp3");
    PlayMusicStream(music);
}

void AudioManager::Update()
{
    UpdateMusicStream(music);
}

void AudioManager::ApplySettings(const Settings &s)
{
    setSfxVolume(s.sfxVolume);
    SetMusicVolume(music, s.musicVolume);

    if (s.musicEnabled)
        PlayMusicStream(music);
    else
        PauseMusicStream(music);
}

void AudioManager::changeSoundState()
{
    if (sfxVolume == 0.0)
    {
        setSfxVolume(1.0);
        settings.sfxVolume = 1.0;
    }
    else
    {
        setSfxVolume(0.0);
        settings.sfxVolume = 0.0;
    }
}

void AudioManager::changeMusicState()
{
    if (IsMusicStreamPlaying(music))
    {
        PauseMusicStream(music);
        settings.musicEnabled = false;
    }
    else
    {
        ResumeMusicStream(music);
        settings.musicEnabled = true;
    }
}

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
