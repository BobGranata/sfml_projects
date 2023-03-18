#pragma once

#include <iostream>
#include <vector>

class Map
{
public:
    enum TileType
    {
        Empty,
        Block,
        OneWay
    };

    const int cTileSize = 16;

    std::vector<TileType> mTiles;
};

