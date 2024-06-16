//
// Created by callum on 15/06/24.
//

#ifndef GL_GRID_ERROR_H
#define GL_GRID_ERROR_H

#include <stdio.h>

#define LOG_ERR(fmt, ...) \
    fprintf(stderr, "ERROR [%s:%s]: " fmt, __FILE__, __func__, ##__VA_ARGS__)

#define LOG_DBG(fmt, ...) \
    printf("DEBUG [%s:%s]: " fmt, __FILE__, __func__, ##__VA_ARGS__)


typedef enum {
    RET_GOOD,
    RET_BAD
} return_t;

#endif //GL_GRID_ERROR_H
