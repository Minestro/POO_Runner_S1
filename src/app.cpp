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

#include "app.h"

using namespace tinyxml2;

App::App(): m_window{"Runner", sf::Style::Default, MODEL_SIZE_W, MODEL_SIZE_H}, m_settings{}, m_gameModel{MODEL_SIZE_W, MODEL_SIZE_H, this}, m_gameView{}, m_menuModel{MODEL_SIZE_W, MODEL_SIZE_H, menuPage::PRE_MENU, this}, m_menuView{}, m_sound{}, m_drawTime{std::chrono::system_clock::now()}, m_drawPeriod{(unsigned int)((1.0f / FPS) * 1000)}, m_running{true}
{
    GraphicElement::loadTextures();
    TextGraphic::loadFonts();
    GraphicElement::loadShaders();
    Sound::loadSoundsBuffers();
    runner::Text::loadLanguages();
    m_sound.setCharacterBuffer("plane.wav");
    try
    {
        Menu::loadModels(this);
    }
    catch (const XMLError &er)
    {
        std::cout << "Error when loading file " << MENU_MODELS_FILE << " . Code : " << std::to_string(er) << std::endl;
        m_menuModel.exitApp();
    }
    Menu::refreshPageContent(&m_menuModel, m_menuModel.getActivePage());
    m_gameView.setModel(&m_gameModel);
    m_gameView.setWindow(&m_window);
    m_menuView.setModel(&m_menuModel);
    m_menuView.setWindow(&m_window);
}

App::~App()
{
    GraphicElement::clearTextures();
    TextGraphic::clearFonts();
    GraphicElement::clearShaders();
    Sound::clearSoundsBuffers();
    m_window.close();
}

Window &App::getWindow()
{
    return m_window;
}

const Window &App::getWindow() const
{
    return m_window;
}

AppSettings &App::getSettings()
{
    return m_settings;
}

const AppSettings &App::getSettings() const
{
    return m_settings;
}
Game &App::getGameModel()
{
    return m_gameModel;
}

const Game &App::getGameModel() const
{
    return m_gameModel;
}

GameView &App::getGameView()
{
    return m_gameView;
}

const GameView &App::getGameView() const
{
    return m_gameView;
}

Menu &App::getMenuModel()
{
    return m_menuModel;
}

const Menu &App::getMenuModel() const
{
    return m_menuModel;
}

MenuView &App::getMenuView()
{
    return m_menuView;
}

const MenuView &App::getMenuView() const
{
    return m_menuView;
}

Sound &App::getSound()
{
    return m_sound;
}

const Sound &App::getSound() const
{
    return m_sound;
}

void App::run()
{
    while (m_running)
    {
        sf::sleep(sf::milliseconds(1));
        if (m_menuModel.getActivePage() == menuPage::ESCAPE_MENU)
        {
            m_gameModel.nextStep();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_drawTime).count() >= m_drawPeriod)
            {
                if (m_gameModel.isPause()) //Si le jeu est en pause, on applique un shader de couche
                {
                    if (m_gameView.getLayeredShader(HUD_Z_INDEX) == nullptr)
                    {
                        m_gameView.addLayeredShader(GraphicElement::m_listShaders[PIXELATE_EFFECT], HUD_Z_INDEX);
                        m_gameView.getLayeredShader(HUD_Z_INDEX)->setParameter("texture", sf::Shader::CurrentTexture);
                        m_gameView.addLayeredShader(GraphicElement::m_listShaders[BLUR_EFFECT], HUD_Z_INDEX+1);
                        m_gameView.getLayeredShader(HUD_Z_INDEX+1)->setParameter("texture", sf::Shader::CurrentTexture);
                    }
                    m_gameView.getLayeredShader(HUD_Z_INDEX)->setParameter("pixel_threshold", m_gameModel.getBlurFade());
                    m_gameView.getLayeredShader(HUD_Z_INDEX+1)->setParameter("blur_radius", m_gameModel.getBlurFade()/2);
                } else if (!m_gameModel.isPause() && m_gameView.getLayeredShader(HUD_Z_INDEX) != nullptr)
                {
                    m_gameView.removeLayeredShader(HUD_Z_INDEX);
                    m_gameView.removeLayeredShader(HUD_Z_INDEX+1);
                }
                m_gameView.synchronise();
                m_gameView.draw();
                m_drawTime = std::chrono::system_clock::now();
            }
            m_running = !m_gameView.treatEvent();
        } else {
            m_sound.playMusic(MUSIC_MENU_FILE);
            m_menuModel.refresh();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_drawTime).count() >= m_drawPeriod)
            {
                m_menuView.synchronise();
                m_menuView.draw();
                m_drawTime = std::chrono::system_clock::now();
            }
            m_running = !m_menuView.treatEvent();
        }
        m_sound.setVolumeMusic(m_settings.m_musicVolume);
        m_sound.setVolumeSounds(m_settings.m_effectVolume);
        m_window.refreshSettings(m_settings);
    }
}

void App::stop()
{
    m_running = false;
}
