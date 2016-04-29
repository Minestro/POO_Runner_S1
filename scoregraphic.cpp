#include "scoregraphic.h"

ScoreGraphic::ScoreGraphic(unsigned int zIndex, float x, float y, const sf::Font *font, unsigned int fontSize, unsigned int refreshPeriod, sf::Color color, int style): GraphicElement::GraphicElement{zIndex, refreshPeriod}, m_showedScore{0}
{
    m_prefixe = new TextElement{zIndex, 0, 0, x, y, "Score : ", font, fontSize, 0, 0, color, style};
    m_score = new TextElement{zIndex, 0, 0, x + m_prefixe->getSize().first, y, std::to_string(0), font, fontSize, 0, 0, color, style};
}

ScoreGraphic::~ScoreGraphic()
{
    delete m_prefixe;
    delete m_score;
}

void ScoreGraphic::setSize(float width, float height)
{
    (void) width;
    (void) height;
}

void ScoreGraphic::setPosition(float x, float y)
{
    m_prefixe->setPosition(x, y);
    m_score->setPosition(x + m_prefixe->getSize().first + 20, y);
}

std::pair<float, float> ScoreGraphic::getSize() const
{
    return {m_prefixe->getSize().first + m_score->getSize().first, m_prefixe->getSize().second};
}

std::pair<float, float> ScoreGraphic::getPosition() const
{
    return m_prefixe->getPosition();
}

std::string ScoreGraphic::getClassName() const
{
    return "ScoreGraphic";
}

void ScoreGraphic::draw(sf::RenderWindow *window) const
{
    m_prefixe->draw(window);
    m_score->draw(window);
}

void ScoreGraphic::refresh(const Element *el, Model *model)
{
    std::vector<std::pair<bool, GameCharacter*> >::const_iterator it = model->getCharacters().begin();
    while (it != model->getCharacters().end() && it->second != el)
    {
        ++it;
    }
    if (it != model->getCharacters().end())
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastRefeshCall).count() >= m_refreshPeriod)
        {
            int deltaScore = (std::max(it->second->getScore(), m_showedScore) - std::min(it->second->getScore(), m_showedScore))/10;
            if (deltaScore < 1)
            {
                deltaScore = 1;
            }
            if (m_showedScore < it->second->getScore())
            {
                m_showedScore += deltaScore;
            } else if (m_showedScore > it->second->getScore())
            {
                m_showedScore -= deltaScore;
            }
            std::string score = std::to_string(m_showedScore);
            while (score.size() < 10)
            {
                score.insert(0, "0");
            }
            m_score->setString(score);
            m_lastRefeshCall = std::chrono::system_clock::now();
        }
    }
}
