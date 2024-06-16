//
// Created by callum on 15/06/24.
//

#include "error.h"
#include "game/game.h"
#include "input/camera.h"
#include "world/cube.h"

#define WINDOW_TITLE                "Another OpenGL Attempt"

#define WINDOW_WIDTH                1920
#define WINDOW_HEIGHT               1080

#define WINDOW_WIDTH_HALF           (WINDOW_WIDTH / 2.0f)
#define WINDOW_HEIGHT_HALF          (WINDOW_HEIGHT / 2.0f)

#define WINDOW_ASPECT_RATIO         ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)
#define WINDOW_FOV                  90.0f
#define WINDOW_NEAR                 0.1f
#define WINDOW_FAR                  100.0f

#define WINDOW_VSYNC                0
#define WINDOW_RESIZABLE            0

#define WINDOW_MAJOR_VERSION        4
#define WINDOW_MINOR_VERSION        5

#define PLAYER_POSITION             (vec3){0.0f, 0.0f, 0.0f}
#define PLAYER_PITCH                0.0f
#define PLAYER_YAW                  (-90.0f)

#define PLAYER_SPEED_MOVE           5.0f
#define PLAYER_SPEED_MOUSE          0.025f

#define GAME_TICKS                  1
#define GAME_TICKS_INVERSE          (1.0f / (float)GAME_TICKS)

static void error_cb(int error, const char *description);

static void keyboard_cb(GLFWwindow *window, int key, int scancode, int action, int mods);

static void frame_buffer_size_cb(GLFWwindow *window, int width, int height);

static void mouse_cb(GLFWwindow *window, int button, int action, int mods);

static void cursor_cb(GLFWwindow *window, double xpos, double ypos);

static void scroll_cb(GLFWwindow *window, double xoffset, double yoffset);

static void game_input_update(game_t *game);

static void game_update(game_t *game);

static void game_time_update(game_t *game);

void game_init(game_t **game) {

    if ((*game = malloc(sizeof(game_t))) == NULL) {
        LOG_ERR("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    /*
     *
     * SCREEN INITIALISATION
     *
     */

    glfwSetErrorCallback(error_cb);

    if (glfwInit() != GL_TRUE) {
        LOG_ERR("Failed to initialise GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WINDOW_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WINDOW_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, WINDOW_RESIZABLE);

    if (((*game)->screen.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL)) == NULL) {
        LOG_ERR("Failed to create GLFW window\n");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent((*game)->screen.window);
    glfwSetInputMode((*game)->screen.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(WINDOW_VSYNC);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        LOG_ERR("Failed to initialise GLEW\n");
        exit(EXIT_FAILURE);
    }

    glm_perspective(WINDOW_FOV, WINDOW_ASPECT_RATIO, WINDOW_NEAR, WINDOW_FAR, (*game)->screen.proj_mat);

    glfwSetKeyCallback((*game)->screen.window, keyboard_cb);
    glfwSetScrollCallback((*game)->screen.window, scroll_cb);
    glfwSetCursorPosCallback((*game)->screen.window, cursor_cb);
    glfwSetMouseButtonCallback((*game)->screen.window, mouse_cb);
    glfwSetFramebufferSizeCallback((*game)->screen.window, frame_buffer_size_cb);

    /*
     *
     * GRAPHICS INITIALISATION
     *
     */

    if (shader_program_create("shaders/vertex/basic.glsl", "shaders/fragment/basic.glsl", &(*game)->graphics.shaders[SHADER_BASIC]) != RET_GOOD) {
        LOG_ERR("Failed to create basic shader program\n");
        exit(EXIT_FAILURE);
    }

    /*
     *
     * PLAYER/CAMERA INITIALISATION
     *
     */

    camera_init(PLAYER_POSITION, PLAYER_PITCH, PLAYER_YAW);

    camera_map((vec3 **) &(*game)->player.position, (float **) &(*game)->player.pitch, (float **) &(*game)->player.yaw);

    /*
     *
     * TIME INITIALISATION
     *
     */

    (*game)->time.delta = 0.0;
    (*game)->time.tick = 0;
    (*game)->time.fps = 0;

    /*
     *
     * WORLD INITIALISATION
     *
     */

    cube_init((*game)->graphics.shaders[SHADER_BASIC]);
}

void game_run(game_t *game) {

    while (glfwWindowShouldClose(game->screen.window) == GL_FALSE) {

        glfwPollEvents();

        game_time_update(game);
        game_input_update(game);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.43f, 0.69f, 1.0f, 1.0f);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        cube_render((*game).screen.proj_mat, (vec4 *) camera_view_matrix());

        glfwSwapBuffers(game->screen.window);

    }
}

static void game_update(game_t *game) {
    // TODO: Update game logic
    LOG_DBG("{%.2f,%.2f,%.2f}[%.2f,%.2f]\n",
            *game->player.position[0],
            *game->player.position[1],
            *game->player.position[2],
            *game->player.pitch,
            *game->player.yaw
    );
}

static void game_time_update(game_t *game) {
    static double time_last;
    static double time_current;
    static double time_accumulated;

    static int frame_count;

    time_current = glfwGetTime();
    game->time.delta = time_current - time_last;
    time_last = time_current;

    time_accumulated += game->time.delta;

    frame_count++;

    if (time_accumulated >= GAME_TICKS_INVERSE) {

        game->time.fps = (int) ((float) frame_count / GAME_TICKS_INVERSE);

        game->time.tick = (game->time.tick + 1) % GAME_TICKS;
        time_accumulated = 0.0;
        frame_count = 0;

        game_update(game);
    }
}

static void game_input_update(game_t *game) {

    vec3 direction = {0.0f, 0.0f, 0.0f};

    if (glfwGetKey(game->screen.window, GLFW_KEY_W) == GLFW_PRESS) direction[2] += 1.0f;
    if (glfwGetKey(game->screen.window, GLFW_KEY_S) == GLFW_PRESS) direction[2] += -1.0f;
    if (glfwGetKey(game->screen.window, GLFW_KEY_A) == GLFW_PRESS) direction[0] += -1.0f;
    if (glfwGetKey(game->screen.window, GLFW_KEY_D) == GLFW_PRESS) direction[0] += 1.0f;

    glm_vec3_scale(direction, PLAYER_SPEED_MOVE * game->time.delta, direction);

    camera_move(direction);
}

static void error_cb(int error, const char *description) {
    LOG_ERR("Error[%d]: %s\n", error, description);
}

static void frame_buffer_size_cb(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void keyboard_cb(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void mouse_cb(GLFWwindow *window, int button, int action, int mods) {

}

static void cursor_cb(GLFWwindow *window, double xpos, double ypos) {
    static double last_x = WINDOW_WIDTH_HALF;
    static double last_y = WINDOW_HEIGHT_HALF;

    double yaw_change = (xpos - last_x) * PLAYER_SPEED_MOUSE;
    double pitch_change = (last_y - ypos) * PLAYER_SPEED_MOUSE;

    last_x = xpos;
    last_y = ypos;

    camera_rotate((float) pitch_change, (float) yaw_change);
}

static void scroll_cb(GLFWwindow *window, double xoffset, double yoffset) {

}
