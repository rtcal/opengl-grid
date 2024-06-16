#include <stdlib.h>

#include "game/game.h"

int main(void) {

    game_t *game = NULL;

    game_init(&game);
    game_run(game);

    return EXIT_SUCCESS;
}