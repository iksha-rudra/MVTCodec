#ifndef MVTCOMMON_H
#define MVTCOMMON_H

#include <vector>
#include <cstdint>
#include "point2di.h"

using namespace std;

namespace MVT
{
    typedef vector<unsigned> GeomEncodeList;

    typedef vector<Point2Di> MultiPoint;

    typedef vector<Point2Di> LineString;

    typedef vector<vector<Point2Di>> MultiLineString;

    typedef vector<vector<Point2Di>> Polygon;

    enum CommandID
    {
        ID_MoveTo = 1,

        ID_LineTo = 2,

        ID_ClosePath = 7
    };

    typedef uint32_t int32;
}

#endif // MVTCOMMON_H
