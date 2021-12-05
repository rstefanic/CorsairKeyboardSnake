#include "BoardDisplay.h"

BoardDisplay::BoardDisplay(Color defaultColor)
{
    m_defaultColor = defaultColor;
    m_size = m_width * m_height;
    m_board = std::vector<Color>(m_size, m_defaultColor);
}

void BoardDisplay::clear()
{
    std::fill(m_board.begin(), m_board.end(), m_defaultColor);
}

bool BoardDisplay::isBlank(int x, int y)
{
    return m_board[getVectorLocation(x, y)] == m_defaultColor;
}

int BoardDisplay::getVectorLocation(int x, int y)
{
    return x + (y * m_width);
}

void BoardDisplay::setColor(int location, Color color)
{
    m_board[location] = color;
}

Color BoardDisplay::getColorAt(int i)
{
    return m_board[i];
}

