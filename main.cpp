#include <iostream>
#include "geometrycodec.h"

using namespace std;

void multilineStringFun()
{
    GeometryCodec geomCodec;

    LineString line1;

    line1.push_back(Point2Di(2,2));

    line1.push_back(Point2Di(2,10));

    line1.push_back(Point2Di(10,10));

    LineString line2;

    line2.push_back(Point2Di(1,1));

    line2.push_back(Point2Di(3,5));

    MultiLineString mulLine;

    mulLine.push_back(line1);

    mulLine.push_back(line2);

    GeomEncodeList list = geomCodec.encodeMultiLineStringGeom(mulLine);

    cout << "[ ";
    for (GeomEncodeList::iterator it = list.begin() ; it != list.end(); ++it)
        cout << " " << *it;
    cout << " ]\n";

    geomCodec.updateGeometry(mulLine);

    for (MultiLineString::iterator it = mulLine.begin() ; it != mulLine.end(); ++it)
    {
        LineString lineStr = *it;

        for (LineString::iterator it = lineStr.begin() ; it != lineStr.end(); ++it)
        {
            Point2Di pnt = *it;

            cout << "(" << pnt.x() << "," << pnt.y() <<")\n";
        }
    }
}

int main()
{
    GeometryCodec geomCodec;

    Polygon poly;

    poly.push_back(Point2Di(3,6));

    poly.push_back(Point2Di(8,12));

    poly.push_back(Point2Di(20,34));

    poly.push_back(Point2Di(3,6));

    GeomEncodeList list = geomCodec.encodePolygonGeom(poly);

    cout << "[ ";
    for (GeomEncodeList::iterator it = list.begin() ; it != list.end(); ++it)
        cout << " " << *it;
    cout << " ]\n";

    return 0;
}

