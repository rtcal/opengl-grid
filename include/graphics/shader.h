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

typedef struct {
    GLuint id;
} shader_program_t;

void shader_init(void);

#endif //GL_GRID_SHADER_H
