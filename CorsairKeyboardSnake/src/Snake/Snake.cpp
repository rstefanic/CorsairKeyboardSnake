#include "Snake.h"

namespace Snake
{
    Snake::Snake(int startPosition, SnakeDirection startDirection, int boardWidth, int boardHeight) : m_snakeDirection(startDirection), m_boardWidth(boardWidth), m_boardHeight(boardHeight)
    {
        assert(startPosition > 3);                                 // Make sure that we have at least 4 spaces to make the snake
        assert(startPosition < ((boardWidth - boardHeight) - 4));  // Make sure that we're not out of bounds on the board

        auto xPosition = (startPosition % m_boardWidth) - 1;
        auto yPosition = (int)startPosition / m_boardWidth;
        m_snake.push_back({ xPosition, yPosition });
        m_snake.push_back({ xPosition - 1, yPosition });
        m_snake.push_back({ xPosition - 2, yPosition });
        m_snake.push_back({ xPosition - 3, yPosition });
    }

    void Snake::move()
    {
        int x = m_snake.front().x;
        int y = m_snake.front().y;
        switch (m_snakeDirection)
        {
        case SnakeDirection::Up:
            y -= 1;
            break;
        case SnakeDirection::Right:
            x += 1;
            break;
        case SnakeDirection::Down:
            y += 1;
            break;
        case SnakeDirection::Left:
            x -= 1;
            break;
        }

        SnakeSegment newSnakeSegment = adjustXOrYIfOutOfBounds(x, y, m_snakeDirection);
        m_snake.push_front(newSnakeSegment); // Advance the head one
        m_snake.pop_back();                  // Remove the tail
    }

    bool Snake::snakeHasCollidedWithSelf()
    {
        auto snakeHead = m_snake.begin();
        for (auto i = snakeHead; i != m_snake.end(); i++)
        {
            if (i != snakeHead &&
                i->x == snakeHead->x &&
                i->y == snakeHead->y)
            {
                return true;
            }
        }

        return false;
    }

    bool Snake::snakeHasCollidedWith(int x, int y)
    {
        auto snakeHead = m_snake.begin();
        return snakeHead->x == x && snakeHead->y == y;
    }

    void Snake::growSnake()
    {
        m_snake.push_back({ m_snake.back().x, m_snake.back().y });
    }

    int Snake::wrapSnakeOnX(SnakeDirection direction)
    {
        assert(direction != SnakeDirection::Up);
        assert(direction != SnakeDirection::Down);

        if (direction == SnakeDirection::Right)
        {
            return 0;
        }

        return m_boardWidth - 1;
    }

    int Snake::wrapSnakeOnY(SnakeDirection direction)
    {
        assert(direction != SnakeDirection::Right);
        assert(direction != SnakeDirection::Left);

        if (direction == SnakeDirection::Down)
        {
            return 0;
        }

        return m_boardHeight - 1;
    }

    SnakeSegment Snake::adjustXOrYIfOutOfBounds(int x, int y, SnakeDirection direction)
    {
        if (xValueIsOutOfBounds(x))
        {
            x = wrapSnakeOnX(m_snakeDirection);
        }

        if (yValueIsOutOfBounds(y))
        {
            y = wrapSnakeOnY(m_snakeDirection);
        }

        return { x, y };
    }
}

