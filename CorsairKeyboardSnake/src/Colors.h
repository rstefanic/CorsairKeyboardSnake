#pragma once

struct Color {
    int r;
    int g;
    int b;

    bool operator==(Color otherColor)
    {
        return r == otherColor.r &&
            g == otherColor.g &&
            b == otherColor.b;
    }
};

constexpr Color defaultBackgroundColor = { 10, 10, 10 };
constexpr Color gameboardColor = { 255, 190, 0 };
constexpr Color snakeBodyColor = { 0, 255, 255 };
constexpr Color snakeHeadColor = { 0, 25, 255 };
constexpr Color foodColor = { 0, 255, 0 };

