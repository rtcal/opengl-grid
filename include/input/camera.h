//
// Created by callum on 15/06/24.
//

#ifndef GL_GRID_CAMERA_H
#define GL_GRID_CAMERA_H

#include <cglm/cglm.h>

void camera_init(vec3 position, float pitch, float yaw);

void camera_map(vec3 **position, float **pitch, float **yaw);

void camera_move(vec3 movement);

void camera_rotate(float pitch_change, float yaw_change);

void camera_teleport(vec3 position, float pitch, float yaw);

const mat4 *camera_view_matrix(void);

#endif //GL_GRID_CAMERA_H
