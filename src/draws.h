#ifndef DRAWS_H
#define DRAWS_H

void init_all_colors();

void calculate_obj_coords(program_condition* condition, WINDOW* second_win);

void draw_stdscr_statics(program_condition* condition);

void editor_redraw(program_condition* condition,
                   WINDOW* main_win,
                   WINDOW* second_win);

#endif