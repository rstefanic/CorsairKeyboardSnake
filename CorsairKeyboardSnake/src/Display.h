#pragma once

#include <vector>

#include "BoardDisplay.h"

/*
 An interface that details the methods needed
 to render the game to a display.
 */
class Display
{
public:
    virtual void render(BoardDisplay) = 0;
    virtual ~Display() {};
};

