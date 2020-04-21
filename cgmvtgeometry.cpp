#include "cgmvtgeometry.h"

CGMVTGeometry::CGMVTGeometry()
{

}

CGMVTGeometry::~CGMVTGeometry()
{

}

GeomEncodeList CGMVTGeometry::encodePoint(Point2Di point)
{
    GeomEncodeList pntList;

    pntList.push_back(encodeParameter(point.first));

    pntList.push_back(encodeParameter(point.second));

    return pntList;
}

GeomEncodeList CGMVTGeometry::encodePoint(vector<Point2Di> pointList)
{
    Point2Di refPnt;

    refPnt.first = 0;

    refPnt.second = 0;

    updatePoint(pointList,refPnt);

    GeomEncodeList cmdlist;

    int32 count = pointList.size();

    cmdlist.push_back(encodeCommand(ID_MoveTo,count));

    GeomEncodeList pntList;

    for (vector<Point2Di>::iterator it = pointList.begin() ; it != pointList.end(); ++it)
    {
        Point2Di pnt = *it;

        pntList.clear();

        pntList = encodePoint(pnt);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    return cmdlist;
}

GeomEncodeList CGMVTGeometry::encodeLineString(LineString lineString)
{
    GeomEncodeList cmdlist;

    cmdlist.push_back(encodeCommand(ID_MoveTo,1));

    GeomEncodeList pntList;

    Point2Di pnt = lineString.at(0);

    pntList = encodePoint(pnt);

    cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));

    int32 count = lineString.size()-1;

    cmdlist.push_back(encodeCommand(ID_LineTo,count));

    for (LineString::iterator it = lineString.begin()+1 ; it != lineString.end(); ++it)
    {
        pnt = *it;

        pntList.clear();

        pntList = encodePoint(pnt);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    return cmdlist;
}

GeomEncodeList CGMVTGeometry::encodeLineString(vector<LineString> lineStringList)
{
    updateLineString(lineStringList);

    GeomEncodeList cmdlist;

    GeomEncodeList pntList;

    for (vector<LineString>::iterator it = lineStringList.begin() ; it != lineStringList.end(); ++it)
    {
        LineString lineStr = *it;

        pntList = encodeLineString(lineStr);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));
    }

    return cmdlist;
}

GeomEncodeList CGMVTGeometry::encodePolygon(vector<Polygon> polygonList)
{
    updatePolygon(polygonList);

    GeomEncodeList cmdlist;

    GeomEncodeList pntList;

    for (vector<Polygon>::iterator it = polygonList.begin() ; it != polygonList.end(); ++it)
    {
        Polygon poly = *it;

        LineString outerPoly = poly.first;

        pntList = encodeLineString(outerPoly);

        cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));

        cmdlist.push_back(encodeCommand(ID_ClosePath,1));

        vector<LineString> innerPoly = poly.second;

        for (vector<LineString>::iterator it = innerPoly.begin() ; it != innerPoly.end(); ++it)
        {
            LineString lineStr = *it;

            pntList = encodeLineString(lineStr);

            cmdlist.insert(end(cmdlist), begin(pntList), end(pntList));

            cmdlist.push_back(encodeCommand(ID_ClosePath,1));
        }
    }

    return cmdlist;
}

int32 CGMVTGeometry::encodeCommand(CommandID id, int32 count)
{
    int32 cInt;

    int32 cid = id;

    cInt = (cid & 0x7) | (count << 3);

    return cInt;
}

int32 CGMVTGeometry::encodeParameter(int value)
{
    return (value << 1) ^ (value >> 31);
}

void CGMVTGeometry::updatePoint(vector<Point2Di> &geomList, Point2Di& refPnt)
{
    for (vector<Point2Di>::iterator it = geomList.begin() ; it != geomList.end(); ++it)
    {
        Point2Di& pnt = *it;

        Point2Di temp = pnt;

        pnt.first = pnt.first - refPnt.first;

        pnt.second = pnt.second - refPnt.second;

        refPnt = temp;
    }
}

void CGMVTGeometry::updateLineString(vector<LineString> &geomList)
{
    Point2Di refPnt;

    refPnt.first = 0;

    refPnt.second = 0;

    for (vector<LineString>::iterator it = geomList.begin() ; it != geomList.end(); ++it)
    {
        LineString& list = *it;

        updatePoint(list, refPnt);
    }
}

void CGMVTGeometry::updatePolygon(vector<Polygon> &geomList)
{
    Point2Di refPnt;

    refPnt.first=0;

    refPnt.second=0;

    Point2Di lastLineTo;

    for (vector<Polygon>::iterator mit = geomList.begin() ; mit != geomList.end(); ++mit)
    {
        Polygon& poly = *mit;

        LineString& outerPoly = poly.first;

        outerPoly.pop_back();

        lastLineTo = outerPoly.at(outerPoly.size()-1);

        updatePoint(outerPoly, refPnt);

        refPnt = lastLineTo;

        vector<LineString>& innerPoly = poly.second;

        for (vector<LineString>::iterator it = innerPoly.begin() ; it != innerPoly.end(); ++it)
        {
            LineString& polyInn = *it;

            polyInn.pop_back();

            lastLineTo = polyInn.at(polyInn.size()-1);

            updatePoint(polyInn, refPnt);

            refPnt = lastLineTo;
        }
    }
}

vector<Point2Di> CGMVTGeometry::decodePoint(GeomEncodeList codedGeomList)
{
    vector<Point2Di> listPoint;

    CommandID cID;

    int32 count;

    Point2Di param;

    Point2Di refPoint(0,0);

    int32 cInt;

    for( int i = 0; i < codedGeomList.size();  )
    {
        cInt = codedGeomList[i++];

        decodeCommand(cInt, cID, count);

        for( int j = 0; j < count; j++)
        {
            cInt = codedGeomList[i++];

            param.first = decodeParameter(cInt);

            cInt = codedGeomList[i++];

            param.second = decodeParameter(cInt);

            param.first = param.first + refPoint.first;

            param.second = param.second + refPoint.second;

            refPoint = param;

            listPoint.push_back(param);
        }
    }

    return listPoint;
}

vector<LineString> CGMVTGeometry::decodeLineString(GeomEncodeList codedGeomList)
{
    vector<LineString> listLineString;

    LineString lineString;

    CommandID cID;

    int32 count;

    Point2Di param;

    Point2Di refPoint(0,0);

    int32 cInt;

    bool refPointSet = false;

    for( int i = 0; i < codedGeomList.size();  )
    {
        cInt = codedGeomList[i++];

        decodeCommand(cInt, cID, count);

        cInt = codedGeomList[i++];

        param.first = decodeParameter(cInt);

        cInt = codedGeomList[i++];

        param.second = decodeParameter(cInt);

        if( refPointSet )
        {
            param.first = param.first + refPoint.first;

            param.second = param.second + refPoint.second;
        }

        refPoint = param;

        lineString.push_back(param);

        cInt = codedGeomList[i++];

        decodeCommand(cInt, cID, count);

        for( int j = 0; j < count; j++)
        {
            cInt = codedGeomList[i++];

            param.first = decodeParameter(cInt);

            cInt = codedGeomList[i++];

            param.second = decodeParameter(cInt);

            param.first = param.first + refPoint.first;

            param.second = param.second + refPoint.second;

            refPoint = param;

            lineString.push_back(param);
        }

        listLineString.push_back(lineString);

        lineString.clear();

        refPointSet = true;
    }

    return listLineString;
}

vector<Polygon> CGMVTGeometry::decodePolygon(GeomEncodeList codedGeomList)
{
    vector<Polygon> polygonList;

    Polygon poly;

    LineString lineString;

    CommandID cID;

    int32 count;

    Point2Di param;

    Point2Di refPoint(0,0);

    int32 cInt;

    bool refPointSet = false;

    int index = 0;

    for( int i = 0; i < codedGeomList.size();  )
    {
        cInt = codedGeomList[i++];

        decodeCommand(cInt, cID, count);

        cInt = codedGeomList[i++];

        param.first = decodeParameter(cInt);

        cInt = codedGeomList[i++];

        param.second = decodeParameter(cInt);

        if( refPointSet )
        {
            param.first = param.first + refPoint.first;

            param.second = param.second + refPoint.second;
        }

        refPoint = param;

        lineString.push_back(param);

        cInt = codedGeomList[i++];

        decodeCommand(cInt, cID, count);

        for( int j = 0; j < count; j++)
        {
            cInt = codedGeomList[i++];

            param.first = decodeParameter(cInt);

            cInt = codedGeomList[i++];

            param.second = decodeParameter(cInt);

            param.first = param.first + refPoint.first;

            param.second = param.second + refPoint.second;

            refPoint = param;

            lineString.push_back(param);
        }

        cInt = codedGeomList[i++];

        decodeCommand(cInt, cID, count);

        if( cID == CommandID::ID_ClosePath)
        {
            lineString.push_back(lineString.at(0));
        }

        if( checkWindingOrder(lineString) > 0.0)
        {
            index++;

            poly.first = lineString;

            polygonList.push_back(poly);
        }
        else
        {
            Polygon& pol = polygonList[index-1];

            pol.second.push_back(lineString);
        }

        lineString.clear();

        refPointSet = true;
    }

    return polygonList;
}

void CGMVTGeometry::decodeCommand(int32 commandInt, CommandID &id, int32 &count)
{
    id = static_cast<CommandID>(commandInt & 0x7);

    count = commandInt >> 3;
}

int CGMVTGeometry::decodeParameter(int32 value)
{
    return ((value >> 1) ^ (-(value & 1)));
}

double CGMVTGeometry::checkWindingOrder(LineString lineString)
{
    double total = 0.0;

    for(unsigned i=0; i < lineString.size(); i++)
    {
        int i2 = (i+1)%lineString.size();

        double val = ((double)(lineString[i2].first) - (double)(lineString[i].first))*
                ((double)(lineString[i2].second) + (double)(lineString[i].second));

        total += val;
    }

    return -total;
}

