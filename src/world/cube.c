//
// Created by callum on 15/06/24.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "world/cube.h"

float vertices[] = {
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f
};
unsigned int indices[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3
};

static struct {
    unsigned int VAO, VBO, EBO;
    unsigned int shader_program;
} cube_instance;

void cube_init(GLuint shader_program) {
    cube_instance.shader_program = shader_program;

    glGenVertexArrays(1, &cube_instance.VAO);
    glGenBuffers(1, &cube_instance.VBO);
    glGenBuffers(1, &cube_instance.EBO);

    glBindVertexArray(cube_instance.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, cube_instance.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_instance.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void cube_render(mat4 view, mat4 projection) {

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_scale(model, (vec3){0.2f, 0.2f, 0.2f});

    glUseProgram(cube_instance.shader_program);

    int model_loc = glGetUniformLocation(cube_instance.shader_program, "m_model");
    int view_loc = glGetUniformLocation(cube_instance.shader_program, "m_view");
    int proj_loc = glGetUniformLocation(cube_instance.shader_program, "m_proj");

    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (const float *) model);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (const float *) view);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (const float *) projection);

    glBindVertexArray(cube_instance.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}