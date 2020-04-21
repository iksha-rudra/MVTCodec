#ifndef CGMVTCOMMON_H
#define CGMVTCOMMON_H

#include <vector>
#include <cstdint>
//#include "point2di.h"

using namespace std;

namespace cgmvt
{
    typedef pair<int, int> Point2Di;

    typedef vector<Point2Di> LineString;

    typedef pair<LineString, vector<LineString>> Polygon;

    enum CommandID
    {
        ID_MoveTo = 1,

        ID_LineTo = 2,

        ID_ClosePath = 7
    };

    enum Geometry
    {
        Type_UnKnown,

        Type_Point,

        Type_LineString,

        Type_Polygon
    };

    enum DataType
    {
        Type_String,

        Type_Float,

        Type_Double,

        Type_Int64,

        Type_UInt64,

        Type_SInt64,

        Type_Bool,
    };

    typedef uint32_t int32;

    typedef vector<int32> GeomEncodeList;
}

#endif // CGMVTCOMMON_H
