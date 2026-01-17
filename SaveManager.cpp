#include "include/SaveManager.h"
#include <fstream>

void SaveManager::SaveData(const Settings &s)
{
    std::ofstream file("settings.cfg");
    if (!file.is_open())
        return;

    file << "sfxVolume=" << s.sfxVolume << "\n";
    file << "musicVolume=" << s.musicVolume << "\n";
    file << "musicEnabled=" << s.musicEnabled << "\n";
}

void SaveManager::LoadData(Settings &s)
{
    std::ifstream file("settings.cfg");
    if (!file.is_open())
        return; // če ne obstaja, ostanejo defaulti

    std::string line;
    while (std::getline(file, line))
    {
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);

        if (key == "sfxVolume")
            s.sfxVolume = std::stof(val);
        if (key == "musicVolume")
            s.musicVolume = std::stof(val);
        if (key == "musicEnabled")
            s.musicEnabled = (val == "1");
    }
}
