//
// Created by callum on 15/06/24.
//

#include <GLFW/glfw3.h>

#include "game/tick.h"

#define TICKS               20
#define TICKS_INVERSE       (1.0f / (float)TICKS)

static double time_last;
static double time_delta;
static double time_current;
static double time_accumulated;

static int frame_count;
static int tick_count;

static int fps;

static void (*tick_callback)(void) = NULL;

int tick_get(void) {
    return tick_count;
}

int fps_get(void) {
    return fps;
}

void tick_init(void) {
    time_last = glfwGetTime();
    time_delta = 0.0;
    time_current = 0.0;
    time_accumulated = 0.0;
    frame_count = 0;
    tick_count = 0;
    fps = 0;
}

void tick_update(void) {

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

        if (tick_callback) {
            tick_callback();
        }
    }

}

void tick_set_callback(void (*callback)(void)) {
    tick_callback = callback;
}

