#include "app.h"

App::App(): m_window{"Runner", sf::Style::Default, GAME_SIZE_W, GAME_SIZE_H}, m_settings{}, m_gameModel{GAME_SIZE_W, GAME_SIZE_H, STARTSPEEDPERIODGAME}, m_gameView{}, m_menuModel{GAME_SIZE_W, GAME_SIZE_H, menuPage::PRE_MENU}, m_menuView{}, m_drawTime{std::chrono::system_clock::now()}, m_drawPeriod{(unsigned int)((1.0f / FPS) * 1000)}, m_running{true}
{
    GraphicElement::loadTextures();
    TextElement::loadFonts();
    GraphicElement::loadShaders();
    m_gameView.setModel(&m_gameModel);
    m_gameView.setWindow(&m_window);
    m_menuView.setModel(&m_menuModel);
    m_menuView.setWindow(&m_window);
    m_gameModel.setApp(*this);
    m_menuModel.setApp(*this);
}

App::~App()
{
    GraphicElement::clearTextures();
    TextElement::clearFonts();
    GraphicElement::clearShaders();
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
                if (m_gameModel.isPause())
                {
                    if (m_gameView.getLayeredShader(6) == nullptr)
                    {
                        m_gameView.addLayeredShader(GraphicElement::m_listShaders[BLUR_EFFECT], 6);
                        m_gameView.getLayeredShader(6)->setParameter("texture", sf::Shader::CurrentTexture);
                    }
                    m_gameView.getLayeredShader(6)->setParameter("blur_radius", m_gameModel.getBlurFade());
                } else if (!m_gameModel.isPause() && m_gameView.getLayeredShader(6) != nullptr)
                {
                    m_gameView.removeLayeredShader(6);
                }
                m_gameView.synchronise();
                m_gameView.draw();
                m_drawTime = std::chrono::system_clock::now();
            }
            m_running = !m_gameView.treatEvent();
        } else {
            m_menuModel.refresh();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_drawTime).count() >= m_drawPeriod)
            {
                m_menuView.synchronise();
                m_menuView.draw();
                m_drawTime = std::chrono::system_clock::now();
            }
            m_running = !m_menuView.treatEvent();
        }
        m_window.refreshSettings(m_settings);
    }
}

void App::stop()
{
    m_running = false;
}
