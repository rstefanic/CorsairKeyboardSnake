#include "UserInput.h"

#ifdef __APPLE__
#pragma message "Input for macOS not currently supported"
#elif _WIN32
#include <Windows.h>
#else
#pragma message "OS not supported"
#endif

Controls::Command Controls::UserInput::getInput()
{
#if _WIN32
    auto keyRight = GetAsyncKeyState(VK_RIGHT) != 0;
    auto keyLeft = GetAsyncKeyState(VK_LEFT) != 0;

    if (keyRight && !m_oldKeyRight) {
        return Command::RIGHT;
    }

    if (keyLeft && !m_oldKeyLeft) {
        return Command::LEFT;
    }

    m_oldKeyLeft = keyLeft;
    m_oldKeyRight = keyRight;
#endif

    return Command::NONE;
}

