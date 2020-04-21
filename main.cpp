#include <iostream>
#include <sstream>

using namespace std;

#include "cgmvectortile.h"

void testMVectorTile()
{
    LineString pointList;

    Polygon poly1;

    pointList.push_back(Point2Di(0,0));

    pointList.push_back(Point2Di(10,0));

    pointList.push_back(Point2Di(10,10));

    pointList.push_back(Point2Di(0,10));

    pointList.push_back(Point2Di(0,0));

    poly1.first = pointList;

    Polygon poly2;

    pointList.clear();

    pointList.push_back(Point2Di(11,11));

    pointList.push_back(Point2Di(20,11));

    pointList.push_back(Point2Di(20,20));

    pointList.push_back(Point2Di(11,20));

    pointList.push_back(Point2Di(11,11));

    poly2.first = pointList;

    pointList.clear();

    pointList.push_back(Point2Di(13,13));

    pointList.push_back(Point2Di(13,17));

    pointList.push_back(Point2Di(17,17));

    pointList.push_back(Point2Di(17,13));

    pointList.push_back(Point2Di(13,13));

    poly2.second.push_back(pointList);

    vector<Polygon> polyList;

    polyList.push_back(poly1);

    polyList.push_back(poly2);

    CGMVectorTile vTile;

    CGMVTLayer* layer = vTile.createLayer();

    layer->setName("TestLayer");

    layer->setExtent(512);

    CGMVTFeature* feature = layer->createFeature();

    feature->setPolygonGeometry(polyList);

    feature->setID(1);

    feature->addAttributes(Type_Int64,"ID","529");

    feature->addAttributes(Type_String,"Name","Rakesh");

    cout << vTile.debugString();
}

int main()
{
    testMVectorTile();

    return 0;
}

