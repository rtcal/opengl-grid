#include <stdlib.h>

#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"

int main(void) {

    window_init();
    shader_init();

    renderer_run();

    window_destroy();

    return EXIT_SUCCESS;
}