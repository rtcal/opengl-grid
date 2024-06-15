cmake_minimum_required(VERSION 3.28)
project(gl_grid C)

set(CMAKE_C_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(cglm REQUIRED)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

file(GLOB_RECURSE SOURCES
        "${PROJECT_SOURCE_DIR}/src/*.c"
)

file(GLOB_RECURSE SHADERS
        "${CMAKE_SOURCE_DIR}/shaders/*.vert"
        "${CMAKE_SOURCE_DIR}/shaders/*.frag"
)

add_executable(
        ${PROJECT_NAME}
        ${SOURCES}
        ${SHADERS}
        main.c
)

target_link_libraries(
        ${PROJECT_NAME}
        OpenGL::GL
        glfw
        GLEW::GLEW
        cglm::cglm
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

target_compile_definitions(${PROJECT_NAME} PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders")


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif ()
