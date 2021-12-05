#include "CorsairKeyboard.h"

void CorsairKeyboard::initialize()
{
    CorsairPerformProtocolHandshake();

    const auto error = CorsairGetLastError();
    if (error) {
        std::cout << "Handshake with Corsair Keyboard failed\n";
        std::cout << convertErrorToString(error);
        return;
    }

    int keyboardDeviceIndex = getCorsairLEDKeyboardDeviceIndex();
    if (keyboardDeviceIndex == -1) {
        std::cout << "No Corsair keyboard with LED keys could be found\n";
        return;
    }

    m_allKeys = getCorsairLedColorKeysByDeviceIndex(keyboardDeviceIndex);
    if (m_allKeys.empty()) {
        return;
    }

    setBackgroundColorOnKeys(m_allKeys);
    m_displayKeys = getKeysUsedForBoardDisplay();
    m_isInitialized = true;
}

const char* CorsairKeyboard::convertErrorToString(CorsairError error)
{
    switch (error) {
    case CE_Success:
        return "Success";
    case CE_ServerNotFound:
        return "Server not found";
    case CE_NoControl:
        return "No Control";
    case CE_ProtocolHandshakeMissing:
        return "Protocol Handshake Missing";
    case CE_IncompatibleProtocol:
        return "Incompatible Protocol";
    case CE_InvalidArguments:
        return "Invalid Arguments";
    default:
        return "Undefined error";
    }
}

int CorsairKeyboard::getCorsairLEDKeyboardDeviceIndex()
{
    const auto numberOfDevices = CorsairGetDeviceCount(); // Only grabs Corsair devices with lighting control

    for (int deviceIndex = 0; deviceIndex < numberOfDevices; deviceIndex++) {
        CorsairDeviceInfo* deviceInfo = CorsairGetDeviceInfo(deviceIndex);

        if (deviceInfo->type == CDT_Keyboard) {
            std::cout << deviceInfo->model << " found. Using keyboard as display...\n";
            return deviceIndex;
        }
    }

    return -1;
}

std::vector<CorsairLedColor> CorsairKeyboard::getCorsairLedColorKeysByDeviceIndex(int deviceIndex)
{
    std::vector<CorsairLedColor> ledKeys;
    const auto ledPositions = CorsairGetLedPositionsByDeviceIndex(deviceIndex);

    if (ledPositions) {
        for (auto i = 0; i < ledPositions->numberOfLed; i++) {
            const auto ledId = ledPositions->pLedPosition[i].ledId;
            ledKeys.push_back(CorsairLedColor{ ledId, 0, 0 ,0 });
        }
    }

    return ledKeys;
}

void CorsairKeyboard::setBackgroundColorOnKeys(std::vector<CorsairLedColor> keys)
{
    for (auto& ledColor : keys) {

        ledColor.r = defaultBackgroundColor.r;
        ledColor.g = defaultBackgroundColor.g;
        ledColor.b = defaultBackgroundColor.b;
    }

    CorsairSetLedsColorsAsync(static_cast<int>(keys.size()), keys.data(), nullptr, nullptr);
}

std::vector<CorsairLedColor> CorsairKeyboard::getKeysUsedForBoardDisplay()
{
    std::vector<CorsairLedColor> displayKeys;
    for (size_t i = CLK_1; i <= CLK_0; i++) { // Keys '1' - '0'
        displayKeys.push_back({ static_cast<CorsairLedId>(i), 0, 0, 0 });
    }

    for (size_t i = CLK_Q; i <= CLK_P; i++) { // Keys 'Q' - 'P'
        displayKeys.push_back({ static_cast<CorsairLedId>(i), 0, 0, 0 });
    }

    for (size_t i = CLK_A; i <= CLK_SemicolonAndColon; i++) { // Keys 'A' - ';'
        displayKeys.push_back({ static_cast<CorsairLedId>(i), 0, 0, 0 });
    }

    for (size_t i = CLK_Z; i <= CLK_SlashAndQuestionMark; i++) { // Keys 'Z' - '/'
        displayKeys.push_back({ static_cast<CorsairLedId>(i), 0, 0, 0 });
    }

    return displayKeys;
}

void CorsairKeyboard::render(BoardDisplay board)
{
    for (int i = 0; i < board.getSize(); i++) {
        auto color = board.getColorAt(i);
        auto* ledKey = &m_displayKeys[i];

        ledKey->r = color.r;
        ledKey->g = color.g;
        ledKey->b = color.b;
    }

    CorsairSetLedsColorsAsync(static_cast<int>(m_displayKeys.size()), m_displayKeys.data(), nullptr, nullptr);
}

