#ifndef CGMVTLAYER_H
#define CGMVTLAYER_H

#include "cgmvtfeature.h"
#include <string>
#include "cgmvtcommon.h"
#include "vector_tile.pb.h"

using namespace vector_tile;

using namespace std;

class CGMVTLayer
{

public:

    ~CGMVTLayer();

    bool setName(string name);

    bool setExtent(uint32_t extend);

    CGMVTFeature *createFeature();

    bool addAttributes(DataType type, string field, string value,
                                    int& keyIndex, int& valueIndex);

private:

    bool _setValue(DataType type, string value,Tile_Value *tileValue);

    CGMVTLayer(Tile_Layer* layer);

    Tile_Layer *m_layer;

    vector<CGMVTFeature*> m_features;

    string m_name;

    uint32_t m_extend;

    friend class CGMVectorTile;

    map<std::string, int> m_keysCache;

    map<std::string, int> m_valuesCache;
};

#endif // CGMVTLAYER_H
