//
// Created by callum on 15/06/24.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "game/game.h"
#include "game/tick.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"

extern GLFWwindow *window_instance;

void game_update(void) {
    printf("TICK[%d], FPS[%d]\n", tick_get(), fps_get());
}

void game_init(void) {
    tick_init();
    shader_init();

    tick_set_callback(game_update);
}

void game_run(void) {

    while (!glfwWindowShouldClose(window_instance)) {

        tick_update();

        renderer_draw();

        glfwPollEvents();
    }
}