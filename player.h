#include <iostream>
#include <vector>
#include "grid.h"

#ifndef OBJHW5_PLAYER_H
#define OBJHW5_PLAYER_H

class Player{
public:
    Grid field, blankField;                     //set field and blankField as a member variable.
    vector<int> horizontalPlacement;
    vector<int> verticalPlacement;
    vector<char> shipPlacementType;
    vector<char> isSunk;
    vector<string> shipName;
    int opponentsHits = 0;
};

#endif