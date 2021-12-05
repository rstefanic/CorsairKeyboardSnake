#pragma once

namespace Snake {
    class Food
    {
    public:
        Food(int x, int y) : m_x(x), m_y(y) {};
        int getX() { return m_x; }
        int getY() { return m_y; }
    private:
        int m_x;
        int m_y;
    };
}

