#pragma once

#include <vector>

#include "Colors.h"
#include "Constants.h"

class BoardDisplay
{
public:
    BoardDisplay(Color defaultColor);
    const int getSize() { return m_size; };
    const int inline getWidth() { return m_width; };
    const int inline getHeight() { return m_height; };
    void clear();
    bool isBlank(int x, int y);
    Color getColorAt(int i);
    std::vector<Color> getBoard() { return m_board; };

protected:
    Color m_defaultColor;
    const int m_width = Constants::boardWidth;
    const int m_height = Constants::boardHeight;
    int m_size;
    std::vector<Color> m_board;

    void setColor(int location, Color color);
    int getVectorLocation(int x, int y);
};

