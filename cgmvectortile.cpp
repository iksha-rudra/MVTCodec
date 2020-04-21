#include "cgmvectortile.h"
#include "cgmvtgeometry.h"
#include <sstream>

CGMVectorTile::CGMVectorTile()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

CGMVectorTile::~CGMVectorTile()
{
    google::protobuf::ShutdownProtobufLibrary();

    for (vector<CGMVTLayer*>::iterator it = m_layers.begin() ; it != m_layers.end(); ++it)
    {
        delete *it;
    }
}

CGMVTLayer *CGMVectorTile::createLayer()
{
    Tile_Layer* tileLayer = m_tile.add_layers();

    CGMVTLayer *layer = new CGMVTLayer(tileLayer);

    m_layers.push_back(layer);

    return layer;
}

bool CGMVectorTile::serializeToString(string* output)
{
    return m_tile.SerializeToString(output);
}

bool CGMVectorTile::parseFromString(const string& data)
{
    return m_tile.ParseFromString(data);
}

bool CGMVectorTile::serializeToOstream(ostream* output)
{
    return m_tile.SerializeToOstream(output);
}

bool CGMVectorTile::parseFromIstream(istream* input)
{
    return m_tile.ParseFromIstream(input);
}

string CGMVectorTile::debugString()
{
    return m_tile.DebugString();
}

bool CGMVectorTile::isInitialized()
{
    return m_tile.IsInitialized();
}

string CGMVectorTile::_featureTypeToStr(int typeIn)
{
    Tile_GeomType type = (Tile_GeomType)typeIn;

    if(type == Tile_GeomType_UNKNOWN)
        return "Unknown";

    if(type == Tile_GeomType_POINT)
        return "Point";

    if(type == Tile_GeomType_LINESTRING)
        return "LineString";

    if(type == Tile_GeomType_POLYGON)
        return "Polygon";

    return "Unknown type";
}

string CGMVectorTile::_valueToStr(const Tile_Value &value)
{
    if(value.has_string_value())
        return value.string_value();

    if(value.has_float_value())
    {
        stringstream ss;
        ss << value.float_value();
        return ss.str();
    }

    if(value.has_double_value())
    {
        stringstream ss;
        ss << value.double_value();
        return ss.str();
    }

    if(value.has_int_value())
    {
        stringstream ss;
        ss << value.int_value();
        return ss.str();
    }

    if(value.has_uint_value())
    {
        stringstream ss;
        ss << value.uint_value();
        return ss.str();
    }

    if(value.has_sint_value())
    {
        stringstream ss;
        ss << value.sint_value();
        return ss.str();
    }

    if(value.has_bool_value())
    {
        stringstream ss;
        ss << value.bool_value();
        return ss.str();
    }

    return "Unknown";
}

bool CGMVectorTile::display()
{
    for(int i = 0; i < m_tile.layers_size(); i++)
    {
        cout << "****Layers****" << endl;

        Tile_Layer layer = m_tile.layers(i);

        cout << "Layer Name: " << layer.name() << endl;

        cout << "Layer Extent: " << layer.extent() << endl;

        vector<string> listKeys;

        for(int i = 0; i < layer.keys_size(); i++)
        {
            string key = layer.keys(i);

            listKeys.push_back(key);
        }

        vector<Tile_Value> listTileValues;

        for(int i=0; i < layer.values_size(); i++)
        {
            Tile_Value tileValue = layer.values(i);

            listTileValues.push_back(tileValue);
        }

        for(int i = 0; i < layer.features_size(); i++)
        {
            cout << "****Feature "<<i<<"****" << endl;

            Tile_Feature feature = layer.features(i);

            cout << "Feature ID: " << feature.id() << endl;

            cout << "****Attributes****" << endl;

            for( int i = 0; i < feature.tags_size(); i++ )
            {
                uint32_t field = feature.tags(i);

                uint32_t value = feature.tags(++i);

                cout << listKeys[field] <<" : "<< _valueToStr(listTileValues[value]) << endl;
            }

            cout << "****Geometry****" << endl;

            cout << "Geom Type: " << _featureTypeToStr(feature.type()) << endl;

            cout << "Geometry Info: " << endl;

            GeomEncodeList geomList;

            for(int i = 0; i < feature.geometry_size(); i++)
            {
                geomList.push_back(feature.geometry(i));
            }

            switch( feature.type() )
            {
                case Tile_GeomType_POINT:
                {
                    vector<Point2Di> pointList = CGMVTGeometry::decodePoint(geomList);

                    for (vector<Point2Di>::iterator it3 = pointList.begin() ;
                         it3 != pointList.end();
                         ++it3)
                    {
                        Point2Di pnt = *it3;

                        cout << "point\n";

                        cout << "(" << pnt.first << "," << pnt.second <<")\n";
                    }

                    break;
                }

                case Tile_GeomType_LINESTRING:
                {
                    vector<LineString> pointList = CGMVTGeometry::decodeLineString(geomList);

                    for (vector<LineString>::iterator it3 = pointList.begin() ;
                         it3 != pointList.end();
                         ++it3)
                    {
                        LineString& pointList = *it3;

                        cout << "line\n";

                        for (LineString::iterator it4 = pointList.begin() ;
                             it4 != pointList.end();
                             ++it4)
                        {
                            Point2Di& pnt = *it4;

                            cout << "(" << pnt.first << "," << pnt.second <<")\n";
                        }
                    }

                    break;
                }

                case Tile_GeomType_POLYGON:
                {
                    vector<Polygon> polygonList = CGMVTGeometry::decodePolygon(geomList);

                    for (vector<Polygon>::iterator it3 = polygonList.begin() ;
                         it3 != polygonList.end();
                         ++it3)
                    {
                        Polygon& poly = *it3;

                        cout << "polygon-Outer\n";

                        LineString lineStr = poly.first;

                        for (LineString::iterator it4 = lineStr.begin() ;
                             it4 != lineStr.end();
                             ++it4)
                        {
                            Point2Di& pnt = *it4;

                            cout << "(" << pnt.first << "," << pnt.second <<")\n";
                        }

                        vector<LineString> lineStrList = poly.second;

                        for (vector<LineString>::iterator it5 = lineStrList.begin() ;
                             it5 != lineStrList.end();
                             ++it5)
                        {
                            cout << "polygon-Inner\n";

                            LineString lineStr = *it5;

                            for (LineString::iterator it6 = lineStr.begin() ;
                                 it6 != lineStr.end();
                                 ++it6)
                            {
                                Point2Di& pnt = *it6;

                                cout << "(" << pnt.first << "," << pnt.second <<")\n";
                            }
                        }
                    }

                    break;
                }
            }
        }
    }
}
