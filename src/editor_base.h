/**/

#ifndef EDITOR_BASE_H
#define EDITOR_BASE_H

enum {
  local_esc_key   =   27,
  local_enter_key = '\n',  // in WINDOWS / DOS    enter key = 13
};

/* color pairs */

enum {
  pair_standard = 20,
  pair_main_win_standard,

  pair_menu_unactive,
  pair_menu_item_non_sel,
  pair_menu_item_sel,

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

typedef enum program_state {
  state_quit = 50,
  state_continue,
  state_continue_and_redraw,

  state_file_submenu,
  state_level_submenu,
  state_misc_submenu,

} program_state;

#endif
