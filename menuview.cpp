#include "menuview.h"

MenuView::MenuView(): m_menuModel{nullptr}
{

}

void MenuView::setModel(Menu *model)
{
    m_menuModel = model;
}

void MenuView::setWindow(Window *window)
{
    m_window = window;
}

void MenuView::insertGraphicElementIntoList(GraphicElement *ge)
{
    std::vector<const GraphicElement*>::iterator it = m_drawableElementsList.begin();
    while(it != m_drawableElementsList.end() && **it < *ge)
    {
        ++it;
    }
    m_drawableElementsList.insert(it, ge);
}

void MenuView::fillGraphicElementsList()
{
    //Cette fonction ajoute dans une liste de tous les graphicElements du tableau de correspondance elementToGraphicElement et qui seront triés suivant leur z-index
    m_drawableElementsList.clear();
    std::map <const Element*, std::list <GraphicElement*> >::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        std::list<GraphicElement*>::const_iterator iterator2 = iterator->second.begin();
        while(iterator2 != iterator->second.end())
        {
            insertGraphicElementIntoList(*iterator2);
            ++iterator2;
        }
        ++iterator;
    }
}

bool MenuView::treatEvent()
{
    bool quitter = false;
    while (m_window->pollEvent(*m_window->getEvent()))
    {
        switch (m_window->getEvent()->type)
        {
        case sf::Event::Closed :
            m_window->close();
            quitter = true;
            break;
        case sf::Event::Resized :
            synchronise();
            break;
        case sf::Event::MouseMoved:
            m_menuModel->setCursorPosition(m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).x, m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).y);
            break;
        case sf::Event::MouseButtonPressed:
            switch (m_window->getEvent()->mouseButton.button)
            {
            case sf::Mouse::Left:
                for (unsigned int i = 0; i<m_menuModel->getButtons().size(); i++)
                {
                    if (m_menuModel->getButtons()[i].second->isHover(m_menuModel->getCursorPosition().first, m_menuModel->getCursorPosition().second))
                    {
                        m_menuModel->getButtons()[i].second->onClick();
                    }
                }
                break;
            default:
                break;
            }
            break;
        case sf::Event::KeyPressed:
            if (m_menuModel->getActivePage() == menuPage::PRE_MENU)
            {
                m_menuModel->setPage(menuPage::HOME);
            }
            break;
        default:
            break;
        }
    }
    return quitter;
}

void MenuView::draw()
{
    m_window->clear();
    fillGraphicElementsList();
    std::vector <const GraphicElement*>::const_iterator iterator = m_drawableElementsList.begin();
    while (iterator != m_drawableElementsList.end())
    {
        (**iterator).draw(m_window);
        ++iterator;
    }
    m_window->display();
}

void MenuView::synchronise()
{
    //Si le menuModel contient des nouveaux élements on les ajoutes à la liste elementToGraphicElement en lui associant un ou plusieurs GraphicElement

    for (unsigned int i=0; i< m_menuModel->getButtons().size(); i++)
    {
        if (m_menuModel->getButtons()[i].first)
        {
            std::map <const Element*, std::list<GraphicElement*> >::const_iterator it = m_elementToGraphicElement.find(m_menuModel->getButtons()[i].second);
            if (it == m_elementToGraphicElement.end())
            {
                std::list<GraphicElement*> list;
                list.push_back(new ButtonGraphic{10, m_menuModel->getButtons()[i].second->getSize().first, m_menuModel->getButtons()[i].second->getSize().second, m_menuModel->getButtons()[i].second->getPosition().first, m_menuModel->getButtons()[i].second->getPosition().second, m_menuModel->getButtons()[i].second->getRotateAngle(), m_menuModel->getButtons()[i].second->getText(), TextElement::m_listFonts["score.ttf"], 20, sf::Color::White});
                m_elementToGraphicElement.insert(std::make_pair(m_menuModel->getButtons()[i].second, list));

            } else {

            }
            m_menuModel->getButtons()[i].first = 0;
        }
    }

    for (unsigned int i=0; i< m_menuModel->getTexts().size(); i++)
    {
         if (m_menuModel->getTexts()[i].first)
         {
             std::map <const Element*, std::list<GraphicElement*> >::const_iterator it = m_elementToGraphicElement.find(m_menuModel->getTexts()[i].second);
             if (it == m_elementToGraphicElement.end())
             {
                 std::list<GraphicElement*> list;
                 list.push_back(new TextElement{10, m_menuModel->getTexts()[i].second->getSize().first, m_menuModel->getTexts()[i].second->getSize().second, m_menuModel->getTexts()[i].second->getPosition().first, m_menuModel->getTexts()[i].second->getPosition().second, m_menuModel->getTexts()[i].second->getRotateAngle(),  m_menuModel->getTexts()[i].second->getText(), TextElement::m_listFonts[m_menuModel->getTexts()[i].second->getFont()], m_menuModel->getTexts()[i].second->getFontSize(), m_menuModel->getTexts()[i].second->getAutoRescale(), m_menuModel->getTexts()[i].second->getWordBreak(), sf::Color{(sf::Uint8)m_menuModel->getTexts()[i].second->getR(), (sf::Uint8)m_menuModel->getTexts()[i].second->getG(), (sf::Uint8)m_menuModel->getTexts()[i].second->getB()}, 0, m_menuModel->getTexts()[i].second->getEffect(), m_menuModel->getTexts()[i].second->getEffectPeriod()});
                 m_elementToGraphicElement.insert(std::make_pair(m_menuModel->getTexts()[i].second, list));
             } else {

             }
         }
    }

    for (unsigned int i=0; i<m_menuModel->getBackgrounds().size(); i++)
    {
        if (m_menuModel->getBackgrounds()[i].first)
        {
            std::map <const Element*, std::list<GraphicElement*> >::const_iterator it = m_elementToGraphicElement.find(m_menuModel->getBackgrounds()[i].second);
            if (it == m_elementToGraphicElement.end())
            {
                std::list<GraphicElement*> list;
                if (m_menuModel->getBackgrounds()[i].second->isSliding())
                {
                    sf::Texture *texture = GraphicElement::m_listTextures[m_menuModel->getBackgrounds()[i].second->getBackgroundFileName()];
                    texture->setRepeated(1);
                    SpriteElement *ge = new SpriteElement{(unsigned int)m_menuModel->getBackgrounds()[i].second->getZIndex(), m_menuModel->getBackgrounds()[i].second->getSize().first, m_menuModel->getBackgrounds()[i].second->getSize().second, m_menuModel->getBackgrounds()[i].second->getPosition().first, m_menuModel->getBackgrounds()[i].second->getPosition().second, m_menuModel->getBackgrounds()[i].second->getRotateAngle(), texture};
                    ge->setTextureRect(sf::IntRect{ge->getTextureRect().left, ge->getTextureRect().top, ge->getTextureRect().width*2, ge->getTextureRect().height});
                    list.push_back(ge);
                    m_elementToGraphicElement.insert(std::make_pair(m_menuModel->getBackgrounds()[i].second, list));
                } else {
                    list.push_back(new SpriteElement{(unsigned int)m_menuModel->getBackgrounds()[i].second->getZIndex(), m_menuModel->getBackgrounds()[i].second->getSize().first, m_menuModel->getBackgrounds()[i].second->getSize().second, m_menuModel->getBackgrounds()[i].second->getPosition().first, m_menuModel->getBackgrounds()[i].second->getPosition().second, m_menuModel->getBackgrounds()[i].second->getRotateAngle(),  GraphicElement::m_listTextures[m_menuModel->getBackgrounds()[i].second->getBackgroundFileName()]});
                    m_elementToGraphicElement.insert(std::make_pair(m_menuModel->getBackgrounds()[i].second, list));
                }
            } else {

            }
            m_menuModel->getBackgrounds()[i].first = 0;
        }
    }

    //Pareil mais si des élements ont été supprimés
    if (m_menuModel->getDeletedElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator deletedElement = m_menuModel->getDeletedElements().begin();
        std::map <const Element*, std::list<GraphicElement*> >::const_iterator it;
        while (deletedElement != m_menuModel->getDeletedElements().end())
        {
            it = m_elementToGraphicElement.find(*deletedElement);
            if (it != m_elementToGraphicElement.end())
            {
                std::list<GraphicElement*>::const_iterator it2 = it->second.begin();
                while(it2 != it->second.end())
                {
                    delete *it2;
                    ++it2;
                }
                delete it->first;
                m_elementToGraphicElement.erase(it);

            }
            ++deletedElement;
        }
        m_menuModel->getDeletedElements().clear();
    }

    //Une fois que l'on a mis à jour notre tableau de correspondance elementToGraphicElement on met à jour leurs positions et leurs tailles
    std::map <const Element*, std::list<GraphicElement*> >::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        std::list<GraphicElement*>::const_iterator iterator2 = iterator->second.begin();
        while (iterator2 != iterator->second.end())
        {
            (**iterator2).refresh(iterator->first, m_menuModel);
            ++iterator2;
        }
        ++iterator;
    }

}
