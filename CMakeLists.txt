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

add_executable(
        ${PROJECT_NAME}
        ${SOURCES}
        main.c
)

target_link_libraries(
        ${PROJECT_NAME}
        OpenGL::GL
        glfw
        GLEW::GLEW
        cglm::cglm
)

set(SHADER_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${SHADER_DIR}
        COMMENT "Removing old shaders directory..."
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders ${SHADER_DIR}
        COMMENT "Copying new shaders directory..."
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders")
