#ifndef CGMVECTORTILE_H
#define CGMVECTORTILE_H

#include "vector_tile.pb.h"

#include "cgmvtlayer.h"

using namespace vector_tile;

using namespace std;

class CGMVectorTile
{

public:
    CGMVectorTile();

    ~CGMVectorTile();

    CGMVTLayer* createLayer();

    bool serializeToString(string* output);

    bool parseFromString(const string& data);

    bool serializeToOstream(ostream* output);

    bool parseFromIstream(istream* input);

    string debugString();

private:

    Tile m_tile;

    vector<CGMVTLayer*> m_layers;
};

#endif // CGMVECTORTILE_H
