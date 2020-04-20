#ifndef GEOMETRYCODEC_H
#define GEOMETRYCODEC_H

#include "mvtcommon.h"
#include "point2di.h"

using namespace MVT;

class GeometryCodec
{

public:
    GeometryCodec();

    ~GeometryCodec();

    GeomEncodeList encodePoint(Point2Di point);

    GeomEncodeList encodePointGeom(Point2Di point);

    GeomEncodeList encodeMultiPointGeom(MultiPoint multiPoint);

    GeomEncodeList encodeLineStringGeom(LineString lineString, bool isUpdated = false);

    GeomEncodeList encodePolygonGeom(Polygon poly, bool isUpdated = false);

    GeomEncodeList encodeMultiLineStringGeom(MultiLineString lineString);

    int32 encodeCommandInteger(CommandID id, int32 count);

    int32 encodeParameterInteger(int value);

    void decodeCommandInteger(int32 commandInt, CommandID& id, int32& count);

    int decodeParameterInteger(int32 value);

    void updateGeometry(MultiPoint& geomList, Point2Di &refPnt);

    void updateGeometry(MultiLineString &geomList);
};

#endif // GEOMETRYCODEC_H
