//
// Created by callum on 15/06/24.
//

#include <stdlib.h>
#include <stdio.h>

#include "graphics/shader.h"
#include "error.h"

#define LOG_BUFFER_LENGTH           512

static shader_program_t SHADER_PROGRAMS[COUNT_SHADERS];

static return_t shader_source_read(const char *filepath, char **content);

static return_t shader_compile(const char *source, GLenum type, GLuint *shader);

static return_t shader_program_create(const char *vpath, const char *fpath, shader_program_t *program);

void shader_init(void) {

    if (shader_program_create("shaders/default.vert", "shaders/default.frag", &SHADER_PROGRAMS[SHADER_DEFAULT]) != RET_GOOD) {
        fprintf(stderr, "ERROR::SHADER::DEFAULT_FAILED\n");
        exit(EXIT_FAILURE);
    }

}

static return_t shader_source_read(const char *filepath, char **content) {

    FILE *file;
    long length;

    if ((file = fopen(filepath, "r")) == NULL) {
        fprintf(stderr, "ERROR::SHADER::FILE_NOT_FOUND %s\n", filepath);
        return RET_BAD;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if ((*content = (char *) malloc(length + 1)) == NULL) {
        fprintf(stderr, "ERROR::SHADER::MEMORY_ALLOCATION_FAILED\n");
        fclose(file);
        return RET_BAD;
    }

    fread(*content, 1, length, file);
    (*content)[length] = '\0';
    fclose(file);

    return RET_GOOD;
}

static return_t shader_compile(const char *source, GLenum type, GLuint *shader) {

    GLint success;
    char infoLog[LOG_BUFFER_LENGTH];

    *shader = glCreateShader(type);

    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        glGetShaderInfoLog(*shader, LOG_BUFFER_LENGTH, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
        glDeleteShader(*shader);
        return RET_BAD;
    }

    return RET_GOOD;
}

static return_t shader_program_create(const char *vpath, const char *fpath, shader_program_t *program) {

    GLint success;
    char *v_source;
    char *f_source;
    GLuint v_shader;
    GLuint f_shader;
    char infoLog[LOG_BUFFER_LENGTH];

    if (shader_source_read(vpath, &v_source) == RET_BAD) {
        fprintf(stderr, "ERROR::SHADER::VERTEX_SHADER_LOADING_FAILED %s\n", vpath);
        return RET_BAD;
    }

    if (shader_source_read(fpath, &f_source) == RET_BAD) {
        fprintf(stderr, "ERROR::SHADER::FRAGMENT_SHADER_LOADING_FAILED %s\n", fpath);
        free(v_source);
        return RET_BAD;
    }

    if (shader_compile(v_source, GL_VERTEX_SHADER, &v_shader) != RET_GOOD) {
        free(v_source);
        free(f_source);
        return RET_BAD;
    }

    if (shader_compile(f_source, GL_FRAGMENT_SHADER, &f_shader) != RET_GOOD) {
        free(v_source);
        free(f_source);
        glDeleteShader(v_shader);
        return RET_BAD;
    }

    program->id = glCreateProgram();

    glAttachShader(program->id, v_shader);
    glAttachShader(program->id, f_shader);
    glLinkProgram(program->id);

    glGetProgramiv(program->id, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        glGetProgramInfoLog(program->id, LOG_BUFFER_LENGTH, NULL, infoLog);
        fprintf(stderr, "ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    free(v_source);
    free(f_source);
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    if (success == GL_FALSE) {
        glDeleteProgram(program->id);
        return RET_BAD;
    }

    return RET_GOOD;
}