//
// Created by callum on 15/06/24.
//

#ifndef GL_GRID_TICK_H
#define GL_GRID_TICK_H

void tick_init(void);

void tick_update(void);

void tick_set_callback(void (*callback)(void));

int tick_get(void);

int fps_get(void);

#endif //GL_GRID_TICK_H
