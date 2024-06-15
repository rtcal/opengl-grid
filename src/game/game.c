//
// Created by callum on 15/06/24.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "game/game.h"
#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"

#define TICKS               20
#define TICKS_INVERSE       (1.0f / (float)TICKS)

extern GLFWwindow *window_instance;

static int tick_count;
static int fps;

void game_update(void) {
    printf("Tick: %d, FPS: %d\n", game_tick_get(), game_fps_get());
}

void game_init(void) {
    window_init();
    shader_init();
}

void game_run(void) {

    static double time_last;
    static double time_delta;
    static double time_current;
    static double time_accumulated;

    static int frame_count;

    while (!glfwWindowShouldClose(window_instance)) {

        time_current = glfwGetTime();
        time_delta = time_current - time_last;
        time_last = time_current;

        time_accumulated += time_delta;

        frame_count++;

        if (time_accumulated >= TICKS_INVERSE) {

            fps = (int) ((float) frame_count / TICKS_INVERSE);

            tick_count = (tick_count + 1) % TICKS;
            time_accumulated = 0.0;
            frame_count = 0;

            game_update();
        }

        renderer_draw();

        glfwPollEvents();
    }

    window_destroy();
}

int game_tick_get(void) {
    return tick_count;
}

int game_fps_get(void) {
    return fps;
}