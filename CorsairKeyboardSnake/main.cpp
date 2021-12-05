#include "src/CorsairKeyboard.h"
#include "src/Snake/Game.h"

int main() {
    CorsairKeyboard keyboard;
    keyboard.initialize();

    if (!keyboard.initalizationSuccessful()) {
        return -1;
    }

    Snake::Game game(keyboard);
    game.run();

    return 0;
}

