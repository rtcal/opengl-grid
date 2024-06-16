//
// Created by callum on 15/06/24.
//

#include "input/camera.h"
#include "error.h"

#define CAMERA_FRONT               (vec3){0.0f, 0.0f, -1.0f}
#define CAMERA_UP                  (vec3){0.0f, 1.0f, 0.0f}

#define CAMERA_PITCH_BOUNDS        89.0f

static struct {
    vec3 position;

    vec3 front;
    vec3 right;

    float pitch_degrees;
    float pitch_radians;

    float yaw_degrees;
    float yaw_radians;

    mat4 view_mat;
} camera_instance;

static void camera_yaw_set(float yaw);

static void camera_pitch_set(float pitch);

static void camera_position_set(vec3 position);

static void camera_update(void);

const mat4 *camera_view_matrix(void) {
    return (mat4 const *) camera_instance.view_mat;
}

void camera_init(vec3 position, float pitch, float yaw) {

    glm_vec3_copy(position, camera_instance.position);

    glm_vec3_copy(CAMERA_FRONT, camera_instance.front);

    camera_yaw_set(yaw);
    camera_pitch_set(pitch);

    camera_update();
}

void camera_map(vec3 **position, float **pitch, float **yaw) {
    *position = &camera_instance.position;
    *pitch = &camera_instance.pitch_degrees;
    *yaw = &camera_instance.yaw_degrees;
}

void camera_move(vec3 movement) {
    vec3 movement_front, movement_right;

    glm_vec3_scale(camera_instance.right, movement[0], movement_right);
    glm_vec3_scale(camera_instance.front, movement[2], movement_front);

    glm_vec3_add(camera_instance.position, movement_right, camera_instance.position);
    glm_vec3_add(camera_instance.position, movement_front, camera_instance.position);

    camera_update();
}

void camera_rotate(float pitch_change, float yaw_change) {
    camera_pitch_set(camera_instance.pitch_degrees + pitch_change);
    camera_yaw_set(camera_instance.yaw_degrees + yaw_change);

    camera_update();
}

void camera_teleport(vec3 position, float pitch, float yaw) {
    camera_position_set(position);
    camera_pitch_set(pitch);
    camera_yaw_set(yaw);

    camera_update();
}

static void camera_position_set(vec3 position) {
    glm_vec3_copy(position, camera_instance.position);
}

static void camera_yaw_set(float yaw) {
    camera_instance.yaw_degrees = fmodf(yaw, 360.0f);
    if (camera_instance.yaw_degrees < 0.0f) camera_instance.yaw_degrees += 360.0f;
    camera_instance.yaw_radians = glm_rad(camera_instance.yaw_degrees);
}

static void camera_pitch_set(float pitch) {
    if (pitch > CAMERA_PITCH_BOUNDS) camera_instance.pitch_degrees = CAMERA_PITCH_BOUNDS;
    else if (pitch < -CAMERA_PITCH_BOUNDS) camera_instance.pitch_degrees = -CAMERA_PITCH_BOUNDS;
    else camera_instance.pitch_degrees = pitch;

    camera_instance.pitch_radians = glm_rad(camera_instance.pitch_degrees);
}

static void camera_update(void) {
    vec3 front, centre;

    front[0] = cosf(camera_instance.yaw_radians) * cosf(camera_instance.pitch_radians);
    front[1] = sinf(camera_instance.pitch_radians);
    front[2] = sinf(camera_instance.yaw_radians) * cosf(camera_instance.pitch_radians);

    glm_vec3_normalize_to(front, camera_instance.front);

    glm_vec3_cross(camera_instance.front, CAMERA_UP, camera_instance.right);
    glm_vec3_normalize(camera_instance.right);

    camera_instance.position[1] = 0.0f;

    glm_vec3_add(camera_instance.position, camera_instance.front, centre);
    glm_lookat(camera_instance.position, centre, CAMERA_UP, camera_instance.view_mat);
}