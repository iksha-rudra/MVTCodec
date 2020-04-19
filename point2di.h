#ifndef POINT2DI_H
#define POINT2DI_H

namespace MVT {

class Point2Di
{
public:

    Point2Di(int x, int y);

    Point2Di();

    int x();

    int y();

    void setX(int x);

    void setY(int y);

    Point2Di operator - (Point2Di const &obj);

    Point2Di operator + (Point2Di const &obj);

private:
    int m_x;

    int m_y;
};

}
#endif // POINT2DI_H
