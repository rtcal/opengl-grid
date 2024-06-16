//
// Created by callum on 15/06/24.
//

#ifndef GL_GRID_CUBE_H
#define GL_GRID_CUBE_H

#include <cglm/cglm.h>

#include "game/game.h"

void cube_init(GLuint shader_program);

void cube_render(mat4 view, mat4 projection);

#endif //GL_GRID_CUBE_H
