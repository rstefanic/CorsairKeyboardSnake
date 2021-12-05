#pragma once

#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#elif _WIN32
#include <CUESDK.h>
#else
#pragma message "OS does not support Corsair CUE SDK"
#endif

#include <iostream>
#include <vector>
#include <unordered_set>
#include <thread>

#include "Colors.h"
#include "Display.h"

#include "Snake/Board.h"

class CorsairKeyboard : public Display
{
public:
    CorsairKeyboard() {};
    void initialize();
    bool initalizationSuccessful() { return m_isInitialized; }
    void render(BoardDisplay board) override;

private:
    bool m_isInitialized = false;
    std::vector<CorsairLedColor> m_allKeys;
    std::vector<CorsairLedColor> m_displayKeys;

    const char* convertErrorToString(CorsairError error);
    int getCorsairLEDKeyboardDeviceIndex();
    std::vector<CorsairLedColor> getCorsairLedColorKeysByDeviceIndex(int deviceIndex);
    void setBackgroundColorOnKeys(std::vector<CorsairLedColor> keys);
    std::vector<CorsairLedColor> getKeysUsedForBoardDisplay();
};

