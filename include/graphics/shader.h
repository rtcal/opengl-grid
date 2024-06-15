//
// Created by callum on 15/06/24.
//

#ifndef GL_GRID_SHADER_H
#define GL_GRID_SHADER_H

#include <GL/glew.h>

typedef enum {
    SHADER_DEFAULT,
    COUNT_SHADERS
} shader_type_e;

void shader_init(void);

void shader_use(shader_type_e type);

#endif //GL_GRID_SHADER_H
