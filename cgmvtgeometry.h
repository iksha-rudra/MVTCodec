#ifndef ENCODEGEOMETRY_H
#define ENCODEGEOMETRY_H

#include "cgmvtcommon.h"
//#include "point2di.h"

using namespace cgmvt;

class CGMVTGeometry
{

public:
    CGMVTGeometry();

    ~CGMVTGeometry();

    static GeomEncodeList encodePoint(Point2Di point);

    static GeomEncodeList encodePoint(vector<Point2Di> pointList);

    static GeomEncodeList encodePolygon(vector<Polygon> polygonList);

    static GeomEncodeList encodeLineString(vector<LineString> lineStringList);

    static GeomEncodeList encodeLineString(LineString lineString);

    static int32 encodeCommand(CommandID id, int32 count);

    static int32 encodeParameter(int value);

    static void updatePoint(vector<Point2Di>& geomList, Point2Di &refPnt);

    static void updateLineString(vector<LineString> &geomList);

    static void updatePolygon(vector<Polygon> &geomList);

    static vector<Point2Di> decodePoint(GeomEncodeList codedGeomList);

    static vector<LineString> decodeLineString(GeomEncodeList codedGeomList);

    static vector<Polygon> decodePolygon(GeomEncodeList codedGeomList);

    static void decodeCommand(int32 commandInt, CommandID& id, int32& count);

    static int decodeParameter(int32 value);

    static double checkWindingOrder(LineString lineString);
};

#endif // ENCODEGEOMETRY_H
