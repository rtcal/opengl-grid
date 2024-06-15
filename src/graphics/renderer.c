//
// Created by callum on 15/06/24.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/renderer.h"

extern GLFWwindow *window_instance;


void renderer_draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.43f, 0.69f, 1.0f, 1.0f);


    glfwSwapBuffers(window_instance);
}
