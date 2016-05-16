#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>

class Tile
{
public:
    int type = 0;// 0 is nothing, 1 is floor, and 2 is walls
    bool checked = false;
    int timesChecked = 0;
    int magnitude = 0;
    bool top = false;
    bool bot = false;
    bool left = false;
    bool right = false;
    bool topedge = false;
    bool botedge = false;
    bool leftedge = false;
    bool rightedge = false;
};

class Map
{
private:

public:
    void setup();
    void draw();

    int size = 10;
    int scale = 3;
    int frequency = 5;
    int biggest = 0;
    std::vector< std::vector<Tile> > symBoardMain;
    std::vector< std::vector<int> > boardMain;
};

class Coordinates
{
public:
    int x;
    int y;
};
