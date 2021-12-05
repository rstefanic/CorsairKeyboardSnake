#pragma once

#include <algorithm>
#include <vector>

#include "../BoardDisplay.h"
#include "../Colors.h"
#include "../Constants.h"

namespace Snake {
    enum class PieceType : char {
        Blank,
        SnakeBody,
        SnakeHead,
        Food
    };

    class Board : public BoardDisplay
    {
    public:
        Board(Color defaultColor);
        void addSnakeBodyTo(int x, int y);
        void addSnakeHeadTo(int x, int y);
        void addFoodTo(int x, int y);
    };
}

