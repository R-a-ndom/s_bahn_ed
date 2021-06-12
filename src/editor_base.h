/**/

#ifndef EDITOR_BASE_H
#define EDITOR_BASE_H

#include "ncurs_ext.h"

#ifdef DEBUG
enum {
  debug_delay = 3000,
};
#endif

enum {
  local_esc_key   =   27,
  local_enter_key = '\n',  // in WINDOWS / DOS    enter key = 13
};

/* color pairs */

enum {
  pair_standard = 20,
  pair_main_win_standard,

  pair_menu_unactive,
  pair_menu_item_unselected,
  pair_menu_item_selected,

  pair_empty,
  pair_wall,
  pair_box,
  pair_player,

  pair_empty_cursor,
  pair_wall_cursor,
  pair_box_cursor,
  pair_player_cursor,
};

/* main window size */

enum {
  terminal_standard_width  = 80,
  terminal_standard_height = 24,

  main_win_width           = 55,
  main_win_height          = 18,
};

/* program state */

typedef enum program_event {
  ev_quit = 50,
  ev_continue,
  ev_continue_and_redraw,
  ev_exit_from_menu,

  ev_file_submenu,
  ev_edit_submenu,
  ev_misc_submenu,

} program_event;

enum {
  second_win_is_submenu,
  second_win_is_other,
  main_menu_unactive = -1,
};

typedef struct program_condition {
  scr_point screen_size;
  scr_point begin_main_win;
  scr_point begin_second_win;
  int main_menu_pos;
  int second_win_state; 
} program_condition;

#endif
