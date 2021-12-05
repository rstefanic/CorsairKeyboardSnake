#pragma once

#include <algorithm>
#include <list>
#include <chrono>
#include <vector>

#include "../Constants.h"
#include "../Display.h"
#include "../UserInput.h"

#include "Board.h"
#include "Food.h"
#include "Snake.h"

namespace Snake {
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    class Game
    {
    public:
        Game(Display& display);
        ~Game();
        void run();

    private:
        Board* m_gameboard;
        Snake* m_snake;
        Food* m_food;

        bool m_isRunning = true;
        Display& m_display;
        Controls::UserInput m_userInput;

        Controls::Command getUserInput();
        void update(Controls::Command command);
        void draw();

        void translateCommandToSnakeDirection(Controls::Command command);
        void createNewFood();
        FoodSegment findLocationForNewFood();

        void addSnakeBodyToBoard();
        void addSnakeHeadToBoard();
        void addFoodToBoard();
    };
}

