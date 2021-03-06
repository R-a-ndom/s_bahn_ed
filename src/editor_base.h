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

  pair_empty_sel,
  pair_wall_sel,
  pair_box_sel,
  pair_player_sel
};


/* main window size */

enum {
  main_win_width = 55,
  main_win_height = 18,
};

/* program state */

typedef enum program_state {
  state_quit = 50,
  state_continue,
  state_continue_and_redraw,
} program_state;


#endif
