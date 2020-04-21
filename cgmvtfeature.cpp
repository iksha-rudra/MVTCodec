#include "cgmvtfeature.h"
#include "cgmvtgeometry.h"
#include "cgmvtlayer.h"

CGMVTFeature::CGMVTFeature(Tile_Feature *feature, CGMVTLayer *parentLayer):
    m_feature(feature),
    m_parentLayer(parentLayer)
{

}

CGMVTFeature::~CGMVTFeature()
{
    google::protobuf::ShutdownProtobufLibrary();
}

bool CGMVTFeature::setID(int id)
{
    m_id = id;

    m_feature->set_id(id);

    return true;
}

bool CGMVTFeature::_setGeometry(GeomEncodeList encodeList)
{
    for( int32 geom: encodeList )
    {
        m_feature->add_geometry(geom);
    }

    return true;
}

bool CGMVTFeature::setPointGeometry(vector<Point2Di>& pointList)
{
    m_feature->set_type(Tile_GeomType_POINT);

    _setGeometry(CGMVTGeometry::encodePoint(pointList));

    return true;
}

bool CGMVTFeature::setLineGeometry(vector<LineString>& lineList)
{
    m_feature->set_type(Tile_GeomType_LINESTRING);

    _setGeometry(CGMVTGeometry::encodeLineString(lineList));

    return true;
}

bool CGMVTFeature::setPolygonGeometry(vector<Polygon>& polygonList)
{
    m_feature->set_type(Tile_GeomType_POLYGON);

    _setGeometry(CGMVTGeometry::encodePolygon(polygonList));

    return true;
}

bool CGMVTFeature::addAttributes(DataType type, string field, string value)
{
    int keyIndex;

    int valueIndex;

    m_parentLayer->addAttributes(type, field, value,
                                keyIndex, valueIndex);

    m_feature->add_tags(keyIndex);

    m_feature->add_tags(valueIndex);

    return true;
}
