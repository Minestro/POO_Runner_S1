/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

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
    std::string m_currentMusic;
public:
    Sound();
    void playSound(std::string sound, bool loop = 0);
    void playMusic(std::string music = "");
    void setVolumeSounds(unsigned int volume);
    void setVolumeMusic(unsigned int volume);
    void setCharacterSoundPitch(float pitch);
    void setCharacterBuffer(std::string buffer);
    void setCharacterSoundPlay(bool play);
    void stopAll();
    void pauseAll();
    void playAll();

    static std::map<std::string, sf::SoundBuffer*> m_listSounds;
    static void loadSoundsBuffers(std::string themeName = "Default");
    static void clearSoundsBuffers();
};

#endif // SOUND_H
