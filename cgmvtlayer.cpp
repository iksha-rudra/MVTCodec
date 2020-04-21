#include "cgmvtlayer.h"
#include <bits/stdc++.h>
#include <sstream>

CGMVTLayer::CGMVTLayer(Tile_Layer* layer):
    m_layer(layer)
{
    m_layer->set_version(15);
}

CGMVTLayer::~CGMVTLayer()
{
    for (vector<CGMVTFeature*>::iterator it = m_features.begin() ; it != m_features.end(); ++it)
    {
        delete *it;
    }
}

bool CGMVTLayer::setName(string name)
{
    m_name = name;

    return true;
}

bool CGMVTLayer::setExtent(uint32_t extend)
{
    m_extend = extend;
}

CGMVTFeature *CGMVTLayer::createFeature()
{
    Tile_Feature* tileFeature = m_layer->add_features();

    CGMVTFeature *feature = new CGMVTFeature(tileFeature,this);

    m_features.push_back(feature);

    return feature;
}

bool CGMVTLayer::addAttributes(DataType type,
                               string field,
                               string value,
                               int &keyIndex,
                               int &valueIndex)
{
    map<std::string, int>::iterator keyChk = m_keysCache.find(field);

    map<std::string, int>::iterator valueChk = m_valuesCache.find(value);

    keyIndex = -1;

    valueIndex = -1;

    if(keyChk == m_keysCache.end())
    {
        m_layer->add_keys(field);

        keyIndex = m_layer->keys_size()-1;

        m_keysCache[field] = keyIndex;
    }
    else
    {
        keyIndex = keyChk->second;
    }

    if(valueChk == m_valuesCache.end())
    {
        Tile_Value *tileValue = m_layer->add_values();

        _setValue(type,value,tileValue);

        valueIndex = m_layer->values_size()-1;

        m_valuesCache[value] = valueIndex;
    }
    else
    {
        valueIndex = valueChk->second;
    }

    return true;
}

bool CGMVTLayer::_setValue(DataType type, string value,Tile_Value *tileValue)
{
    switch(type)
    {
        case Type_String:
        {
            tileValue->set_string_value(value);

            break;
        }

        case Type_Float:
        {
            stringstream stream(value);

            float fVal;

            stream >> fVal;

            tileValue->set_float_value(fVal);

            break;
        }

        case Type_Double:
        {
            stringstream stream(value);

            double fVal;

            stream >> fVal;

            tileValue->set_double_value(fVal);

            break;
        }

        case Type_Int64:
        case Type_SInt64:
        {
            stringstream stream(value);

            int64_t fVal;

            stream >> fVal;

            tileValue->set_sint_value(fVal);

            break;
        }

        case Type_UInt64:
        {
            stringstream stream(value);

            uint64_t fVal;

            stream >> fVal;

            tileValue->set_uint_value(fVal);

            break;
        }

        case Type_Bool:
        {
            stringstream stream(value);

            bool fVal;

            stream >> fVal;

            tileValue->set_bool_value(fVal);

            break;
        }
    }
}



