//
// Created by callum on 15/06/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/window.h"

#define WINDOW_TITLE                "GRID"

#define WINDOW_WIDTH                1920
#define WINDOW_HEIGHT               1080

GLFWwindow *window_instance;

static void error_callback(int error, const char *description);

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void window_init(void) {

    glfwSetErrorCallback(error_callback);

    if (glfwInit() != GL_TRUE) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_instance = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (window_instance == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_instance);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(0);

    glfwSetKeyCallback(window_instance, key_callback);
    glfwSetFramebufferSizeCallback(window_instance, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window_instance, mouse_button_callback);
    glfwSetCursorPosCallback(window_instance, cursor_position_callback);
    glfwSetScrollCallback(window_instance, scroll_callback);
}

void window_destroy(void) {
    glfwDestroyWindow(window_instance);
    glfwTerminate();
}

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error[%d]: %s\n", error, description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Handle left mouse button press
    }
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    // Handle cursor position changes
}

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Handle scroll input
}
