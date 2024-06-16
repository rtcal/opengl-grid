//
// Created by callum on 15/06/24.
//

#ifndef GL_GRID_GAME_H
#define GL_GRID_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "graphics/shader.h"

typedef enum {
    SHADER_BASIC,
    COUNT_SHADERS
} shader_type_e;

typedef struct {

    struct {
        GLFWwindow *window;
        mat4 proj_mat;
    } screen;

    struct {
        GLuint shaders[COUNT_SHADERS];
    } graphics;

    struct {
        const vec3 *position;
        const float *pitch;
        const float *yaw;
    } player;

    struct {
        double delta;
        int tick;
        int fps;
    } time;

} game_t;

void game_init(game_t **game);

void game_run(game_t *game);

#endif //GL_GRID_GAME_H
