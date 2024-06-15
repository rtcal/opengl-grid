//
// Created by callum on 15/06/24.
//

#include <GLFW/glfw3.h>
#include "graphics/renderer.h"

extern GLFWwindow *window_instance;

void renderer_run(void) {
    while (!glfwWindowShouldClose(window_instance)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window_instance);
        glfwPollEvents();
    }
}