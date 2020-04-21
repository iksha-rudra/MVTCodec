#include "cgmvectortile.h"

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
