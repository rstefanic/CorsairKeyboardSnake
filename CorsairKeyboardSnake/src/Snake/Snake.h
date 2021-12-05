#pragma once

#include <assert.h>
#include <list>
#include <iostream>

namespace Snake
{
    struct SnakeSegment
    {
        int x;
        int y;
    };


    using FoodSegment = SnakeSegment;

    enum class SnakeDirection
    {
        Up,
        Right,
        Down,
        Left
    };

    class Snake
    {
    public:
        Snake(int startPosition, SnakeDirection startDirection, int boardWidth, int boardHeight);

        std::list<SnakeSegment> getSnake() const { return m_snake; }
        SnakeDirection getSnakeDirection() const { return m_snakeDirection; };
        void changeDirection(SnakeDirection direction) { m_snakeDirection = direction; };

        void move();
        bool snakeHasCollidedWithSelf();
        bool snakeHasCollidedWith(int x, int y);
        void growSnake();
        size_t snakeLength() const { return m_snake.size(); };

    private:
        const int m_boardWidth;
        const int m_boardHeight;

        std::list<SnakeSegment> m_snake;
        SnakeDirection m_snakeDirection;

        bool xValueIsOutOfBounds(int x)
        {
            return x < 0 || x >= m_boardWidth;
        };

        bool yValueIsOutOfBounds(int y)
        {
            return y < 0 || y >= m_boardHeight;
        };

        int wrapSnakeOnX(SnakeDirection direction);
        int wrapSnakeOnY(SnakeDirection direction);
        SnakeSegment adjustXOrYIfOutOfBounds(int x, int y, SnakeDirection direction);
    };
}

