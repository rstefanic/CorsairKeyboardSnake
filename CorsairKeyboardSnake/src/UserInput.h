#pragma once

namespace Controls {
    enum class Command {
        NONE,
        LEFT,
        RIGHT
    };

    class UserInput
    {
    public:
        Command getInput();

    private:
        bool m_oldKeyLeft = false;
        bool m_oldKeyRight = false;
    };
}

