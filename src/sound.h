#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <list>
#include <map>
#include <iostream>
#include "const.h"

class Sound
{
private:
    sf::Sound m_sounds;
    sf::Sound m_characterSound;
    sf::Music m_music;
public:
    Sound();
    void playSound(std::string sound, bool loop = 0);
    void playMusic(std::string music);
    void setVolumeSounds(unsigned int volume);
    void setVolumeMusic(unsigned int volume);
    void setCharacterSoundPitch(float pitch);
    void setCharacterBuffer(std::string buffer);
    void setCharacterSoundPlay(bool play);
    void stopAll();

    static std::map<std::string, sf::SoundBuffer*> m_listSounds;
    static void loadSoundsBuffers(std::string themeName = "Default");
    static void clearSoundsBuffers();
};

#endif // SOUND_H
