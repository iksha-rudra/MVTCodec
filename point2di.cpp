#include "point2di.h"

using namespace MVT;

Point2Di::Point2Di()
{
    m_x = 0;

    m_y = 0;
}

Point2Di::Point2Di(int x, int y)
{
    m_x = x;

    m_y = y;
}

int Point2Di::x()
{
    return m_x;
}

int Point2Di::y()
{
    return m_y;
}

void Point2Di::setX(int x)
{
    m_x = x;
}

void Point2Di::setY(int y)
{
    m_y = y;
}

Point2Di Point2Di::operator - (Point2Di const &obj)
{
    Point2Di res;

    res.m_x = this->m_x - obj.m_x;

    res.m_y = this->m_y - obj.m_y;

    return res;
}

Point2Di Point2Di::operator + (Point2Di const &obj)
{
    Point2Di res;

    res.m_x = this->m_x + obj.m_x;

    res.m_y = this->m_y + obj.m_y;

    return res;
}

