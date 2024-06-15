//
// Created by callum on 15/06/24.
//

#include <GLFW/glfw3.h>

#include "graphics/renderer.h"

extern GLFWwindow *window_instance;

void renderer_draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // other drawing stuff here

    glfwSwapBuffers(window_instance);
}