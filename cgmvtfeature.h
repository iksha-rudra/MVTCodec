#ifndef CGMVTFEATURE_H
#define CGMVTFEATURE_H

#include <string>

#include "cgmvtcommon.h"

#include "vector_tile.pb.h"

using namespace vector_tile;

using namespace cgmvt;

using namespace std;

class CGMVTLayer;

class CGMVTFeature
{

public:

    ~CGMVTFeature();

    bool setID(int id);

    bool setPointGeometry(vector<Point2Di> &pointList);

    bool setLineGeometry(vector<LineString> &lineList);

    bool setPolygonGeometry(vector<Polygon> &polygonList);

    bool addAttributes(DataType type, string field, string value);

private:

    CGMVTFeature(Tile_Feature *feature, CGMVTLayer *parentLayer);

    bool _setGeometry(GeomEncodeList encodeList);

    Tile_Feature *m_feature;

    CGMVTLayer *m_parentLayer;

    int m_id;

    friend class CGMVTLayer;
};

#endif // CGMVTFEATURE_H
