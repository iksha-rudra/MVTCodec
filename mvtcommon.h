#ifndef MVTCOMMON_H
#define MVTCOMMON_H

#include <vector>
#include <cstdint>
#include "point2di.h"

namespace MVT
{
    typedef std::vector<unsigned> GeomEncodeList;

    typedef std::vector<Point2Di> MultiPoint;

    typedef MultiPoint LineString;

    typedef MultiPoint Polygon;

    typedef std::vector<LineString> MultiLineString;

    typedef std::vector<Polygon> MultiPolygon;

    enum CommandID
    {
        ID_MoveTo = 1,

        ID_LineTo = 2,

        ID_ClosePath = 7
    };

    typedef uint32_t int32;
}

#endif // MVTCOMMON_H
