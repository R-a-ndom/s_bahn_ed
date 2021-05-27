#ifndef DRAWS_H
#define DRAWS_H

enum {
  draw_main_menu,
  no_draw_main_menu,
};

void init_all_colors();

void calculate_obj_coords(editor_obj_coords* coords);

void draw_stdscr_statics(editor_obj_coords* coords);

void editor_redraw(WINDOW* main_win, editor_obj_coords* coords, int need_to_draw_menu);

#endif