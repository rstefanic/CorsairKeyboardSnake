#include "Board.h"

Snake::Board::Board(Color defaultColor) : BoardDisplay(defaultColor) {}

void Snake::Board::addSnakeBodyTo(int x, int y)
{
    setColor(getVectorLocation(x, y), snakeBodyColor);
}

void Snake::Board::addSnakeHeadTo(int x, int y)
{
    setColor(getVectorLocation(x, y), snakeHeadColor);
}

void Snake::Board::addFoodTo(int x, int y)
{
    setColor(getVectorLocation(x, y), foodColor);
}

