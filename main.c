#include <stdlib.h>

#include "graphics/window.h"
#include "game/game.h"

int main(void) {

    window_init();
    game_init();

    game_run();

    window_destroy();

    return EXIT_SUCCESS;
}