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

#include "sound.h"

std::map<std::string, sf::SoundBuffer*> Sound::m_listSounds;

Sound::Sound(): m_sounds{}, m_characterSound{}, m_music{}, m_currentMusic{}
{
}

void Sound::loadSoundsBuffers(std::string themeName)
{
    m_listSounds.clear();
    std::map<std::string, sf::SoundBuffer*>::iterator iterator = m_listSounds.begin();
    for (unsigned int i=0; i<sizeof(SOUNDS_LIST)/sizeof(*SOUNDS_LIST); i++)
    {
        iterator = m_listSounds.insert(iterator, std::make_pair(SOUNDS_LIST[i], new sf::SoundBuffer));
        if (!(iterator->second->loadFromFile("Ressources/" + themeName + "/Sounds/" + SOUNDS_LIST[i])))
        {

        }
    }
}

void Sound::clearSoundsBuffers()
{
    std::map<std::string, sf::SoundBuffer*>::iterator iterator = m_listSounds.begin();
    while (iterator != m_listSounds.end())
    {
        delete iterator->second;
        ++iterator;
    }
    m_listSounds.clear();
}

void Sound::playSound(std::string sound, bool loop)
{
    m_sounds.setBuffer(*m_listSounds[sound]);
    m_sounds.setLoop(loop);
    m_sounds.play();
}

void Sound::playMusic(std::string music)
{
    if (m_currentMusic != music || m_music.getStatus() != sf::Sound::Status::Playing)
    {
        if (music == "")
        {
            music = m_currentMusic;
        }
        if (!m_music.openFromFile(music))
        {

        }
        m_music.setLoop(1);
        m_currentMusic = music;
        m_music.play();
    }
}

void Sound::setVolumeMusic(unsigned int volume)
{
    m_music.setVolume(volume);
}

void Sound::setVolumeSounds(unsigned int volume)
{
    m_sounds.setVolume(volume);
    m_characterSound.setVolume(volume);
}

void Sound::setCharacterSoundPitch(float pitch)
{
    m_characterSound.setPitch(pitch);
}

void Sound::setCharacterBuffer(std::string buffer)
{
    m_characterSound.setBuffer(*m_listSounds[buffer]);
    m_characterSound.setLoop(1);
    m_characterSound.play();
    m_characterSound.pause();
}

void Sound::setCharacterSoundPlay(bool play)
{
    if (!play && m_characterSound.getStatus() == sf::Sound::Status::Playing)
    {
        m_characterSound.pause();
    } else if (play && (m_characterSound.getStatus() == sf::Sound::Status::Paused || m_characterSound.getStatus() == sf::Sound::Status::Stopped))
    {
        m_characterSound.play();
    }
}

void Sound::stopAll()
{
    m_sounds.stop();
    m_music.stop();
    m_characterSound.stop();
}

void Sound::pauseAll()
{
    m_sounds.pause();
    m_music.pause();
    m_characterSound.pause();
}

void Sound::playAll()
{
    m_sounds.play();
    m_music.play();
    m_characterSound.play();
}
