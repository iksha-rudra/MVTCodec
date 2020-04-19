#include "geometrycodec.h"

using std::begin;
using std::end;

GeometryCodec::GeometryCodec()
{

}

GeometryCodec::~GeometryCodec()
{

}

GeomEncodeList GeometryCodec::encodePoint(Point2Di point)
{
    GeomEncodeList pntList;

    pntList.push_back(encodeParameterInteger(point.x()));

    pntList.push_back(encodeParameterInteger(point.y()));

    return pntList;
}

GeomEncodeList GeometryCodec::encodePointGeom(Point2Di point)
{
    GeomEncodeList cmdlist;

    cmdlist.push_back(encodeCommandInteger(ID_MoveTo,1));

    GeomEncodeList pntList;

    pntList = encodePoint(point);

    cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));

    return cmdlist;
}

GeomEncodeList GeometryCodec::encodeMultiPointGeom(MultiPoint multiPoint)
{
    Point2Di refPnt(0,0);

    updateGeometry(multiPoint,refPnt);

    GeomEncodeList cmdlist;

    int32 count = multiPoint.size();

    cmdlist.push_back(encodeCommandInteger(ID_MoveTo,count));

    GeomEncodeList pntList;

    for (MultiPoint::iterator it = multiPoint.begin() ; it != multiPoint.end(); ++it)
    {
        Point2Di pnt = *it;

        pntList.clear();

        pntList = encodePoint(pnt);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    return cmdlist;
}

GeomEncodeList GeometryCodec::encodeLineStringGeom(LineString lineString, bool isUpdated)
{
    if( !isUpdated )
    {
        Point2Di refPnt(0,0);

        updateGeometry(lineString, refPnt);
    }

    GeomEncodeList cmdlist;

    cmdlist.push_back(encodeCommandInteger(ID_MoveTo,1));

    GeomEncodeList pntList;

    Point2Di pnt = lineString.at(0);

    pntList = encodePoint(pnt);

    cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));

    int32 count = lineString.size()-1;

    cmdlist.push_back(encodeCommandInteger(ID_LineTo,count));

    for (MultiPoint::iterator it = lineString.begin()+1 ; it != lineString.end(); ++it)
    {
        pnt = *it;

        pntList.clear();

        pntList = encodePoint(pnt);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    return cmdlist;
}

GeomEncodeList GeometryCodec::encodeMultiLineStringGeom(MultiLineString lineString)
{
    updateGeometry(lineString);

    GeomEncodeList cmdlist;

    for (MultiLineString::iterator it = lineString.begin() ; it != lineString.end(); ++it)
    {
        LineString lineStr = *it;

        GeomEncodeList pntList;

        pntList = encodeLineStringGeom(lineStr,true);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    return cmdlist;
}

GeomEncodeList GeometryCodec::encodePolygonGeom(Polygon poly, bool isUpdated)
{
    if( !isUpdated )
    {
        Point2Di refPnt(0,0);

        updateGeometry(poly, refPnt);
    }

    GeomEncodeList cmdlist;

    cmdlist.push_back(encodeCommandInteger(ID_MoveTo,1));

    GeomEncodeList pntList;

    Point2Di pnt = poly.at(0);

    pntList = encodePoint(pnt);

    cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));

    int32 count = poly.size()-2;

    cmdlist.push_back(encodeCommandInteger(ID_LineTo,count));

    for (MultiPoint::iterator it = poly.begin()+1 ; it != poly.end()-1; ++it)
    {
        pnt = *it;

        pntList.clear();

        pntList = encodePoint(pnt);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    cmdlist.push_back(encodeCommandInteger(ID_ClosePath,1));

    return cmdlist;
}

int32 GeometryCodec::encodeCommandInteger(CommandID id, int32 count)
{
    int32 cInt;

    int32 cid = id;

    cInt = (cid & 0x7) | (count << 3);

    return cInt;
}

void GeometryCodec::decodeCommandInteger(int32 commandInt, CommandID &id, int32 &count)
{
    id = static_cast<CommandID>(commandInt & 0x7);

    count = commandInt >> 3;
}

int32 GeometryCodec::encodeParameterInteger(int value)
{
    return (value << 1) ^ (value >> 31);
}

int GeometryCodec::decodeParameterInteger(int32 value)
{
    return ((value >> 1) ^ (-(value & 1)));
}

void GeometryCodec::updateGeometry(MultiPoint &geomList, Point2Di& refPnt)
{
    for (MultiPoint::iterator it = geomList.begin() ; it != geomList.end(); ++it)
    {
        Point2Di pnt = *it;

        *it = *it - refPnt;

        refPnt = pnt;
    }
}

void GeometryCodec::updateGeometry(MultiLineString &geomList)
{
    Point2Di refPnt(0,0);

    for (MultiLineString::iterator mit = geomList.begin() ; mit != geomList.end(); ++mit)
    {
        LineString& list = *mit;

        updateGeometry(list, refPnt);
    }
}

