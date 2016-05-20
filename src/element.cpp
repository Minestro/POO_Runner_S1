#include "element.h"

ColorRGBA::ColorRGBA(): r{255}, g{255}, b{255}, a{0}
{

}

ColorRGBA::ColorRGBA(unsigned int cr, unsigned int cg, unsigned int cb, unsigned int alpha): r{cr}, g{cg}, b{cb}, a{alpha}
{

}

const ColorRGBA ColorRGBA::White = ColorRGBA{255, 255, 255};
const ColorRGBA ColorRGBA::Black = ColorRGBA{0, 0, 0};

Element::Element(float x, float y, float w, float h, float rotation, unsigned long int id): m_id{id}, m_position{x, y}, m_size{w, h}, m_rotation{rotation}
{

}

std::pair<float, float> Element::getSize() const
{
    return m_size;
}
std::pair<float, float> Element::getPosition() const
{
    return m_position;
}

void Element::setSize(float w, float h)
{
    m_size.first = w;
    m_size.second = h;
}
void Element::setPosition(float x, float y)
{
    m_position.first=x;
    m_position.second=y;
}

//------------------------------------------------------------------------------
// Input:   el : second élement avec lequel on veut tester la collision
// Output:  Rien
// Return:  Booléen
// Purpose: Fonction qui renvoie si deux élements (rectangles) sont en collision
// en fonction de leur rotation
//------------------------------------------------------------------------------
bool Element::collision(const Element *el) const
{
    if ((int)getRotateAngle()%360 == 0 && (int)el->getRotateAngle()%360 ==0)
    {
        return ((el->getPosition().first < m_position.first + m_size.first && el->getPosition().first + el->getSize().first > m_position.first) && (el->getPosition().second < m_position.second + m_size.second && el->getPosition().second + el->getSize().second > m_position.second));
    } else {
        std::vector<std::vector<std::pair<float, float> > > points;
        std::vector<const Element*> rectangles;
        std::vector<std::pair<float, float> > axis;
        rectangles.push_back(this);
        rectangles.push_back(el);
        points.resize(rectangles.size());


        for (unsigned int i=0; i<rectangles.size(); i++)
        {
            points[i] = rectangles[i]->getPointsAfterRotation();
        }


        axis.push_back(std::make_pair(points[0][UR].first - points[0][UL].first, points[0][UR].second - points[0][UL].second));
        axis.push_back(std::make_pair(points[0][UR].first - points[0][DR].first, points[0][UR].second - points[0][DR].second));
        axis.push_back(std::make_pair(points[1][UL].first - points[1][DL].first, points[1][UL].second - points[1][DL].second));
        axis.push_back(std::make_pair(points[1][UL].first - points[1][UR].first, points[1][UL].second - points[1][UR].second));
        bool collision = true;
        unsigned int i =0;
        while (i<axis.size() && collision)
        {
            std::vector<std::vector<int> > scalarValuesPoints;
            scalarValuesPoints.resize(rectangles.size());
            for (unsigned int j=0; j<rectangles.size(); j++)
            {
                for (unsigned int k=0; k<points[j].size(); k++)
                {
                    std::pair<float, float> resultPointOnAxis;
                    resultPointOnAxis.first = (points[j][k].first*axis[i].first + points[j][k].second*axis[i].second)/(pow(axis[i].first, 2) + pow(axis[i].second, 2))*axis[i].first;
                    resultPointOnAxis.second = (points[j][k].first*axis[i].first + points[j][k].second*axis[i].second)/(pow(axis[i].first, 2) + pow(axis[i].second, 2))*axis[i].second;
                    scalarValuesPoints[j].push_back(resultPointOnAxis.first * axis[i].first + resultPointOnAxis.second * axis[i].second);
                }
            }
            int minA, minB, maxA, maxB;
            minA = maxA = *scalarValuesPoints[0].begin();
            minB = maxB = *scalarValuesPoints[1].begin();

            for (int scalarValue : scalarValuesPoints[0])
            {
                if (scalarValue < minA)
                {
                    minA = scalarValue;
                }
                if (scalarValue > maxA)
                {
                    maxA = scalarValue;
                }
            }

            for (int scalarValue : scalarValuesPoints[1])
            {
                if (scalarValue < minB)
                {
                    minB = scalarValue;
                }
                if (scalarValue > maxB)
                {
                    maxB = scalarValue;
                }
            }

            if (!(minB <= maxA && maxB >= minA))
            {
                collision = false;
            }
            i++;
        }
        return collision;
    }
}

std::vector<std::pair<float, float> > Element::getPointsAfterRotation() const
{
    std::vector<std::pair<float, float> > points;
    std::pair<float, float> Origin = std::make_pair(getSize().first / 2, getSize().second / 2);
    std::pair<float, float> Pos = std::make_pair(getPosition().first + Origin.first, getPosition().second + Origin.second);
    std::pair<float, float> Ao{-Origin.first, -Origin.second};
    std::pair<float, float> Bo{Origin.first, -Origin.second};
    std::pair<float, float> Co{-Origin.first, Origin.second};
    std::pair<float, float> Do{Origin.first, Origin.second};
    float rotation = getRotateAngle()*(PI/180);
    points.resize(4);

    points[UL] = std::make_pair(Ao.first * cos(rotation) - Ao.second * sin(rotation) + Pos.first, Ao.second * cos(rotation) + Ao.first * sin(rotation) + Pos.second);

    points[UR] = std::make_pair(Bo.first * cos(rotation) - Bo.second * sin(rotation) + Pos.first, Bo.second * cos(rotation) + Bo.first * sin(rotation) + Pos.second);

    points[DL] = std::make_pair(Co.first * cos(rotation) - Co.second * sin(rotation) + Pos.first, Co.second * cos(rotation) + Co.first * sin(rotation) + Pos.second);

    points[DR] = std::make_pair(Do.first * cos(rotation) - Do.second * sin(rotation) + Pos.first, Do.second * cos(rotation) + Do.first * sin(rotation) + Pos.second);
    return points;
}

std::pair<float, float> Element::getPixelSpeed() const
{
    return (std::make_pair<float, float>(0.0, 0.0));
}

float Element::getRotateAngle() const
{
    return m_rotation;
}

unsigned long Element::getId() const
{
    return m_id;
}

void Element::setId(unsigned long int id)
{
    m_id = id;
}
