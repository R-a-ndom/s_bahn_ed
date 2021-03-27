/*

*/

#ifndef S_EDITOR_H
#define S_EDITOR_H

/* screen size and object coords */

typedef struct editor_obj_coords {
  scr_point screen_size;
  scr_point coords_main_win;
} editor_obj_coords;


void draw_stdscr_statics(editor_obj_coords* coords);

void editor_init();

void editor_run();

#endif
