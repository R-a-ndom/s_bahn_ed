/**/

#ifndef EDITOR_BASE_H
#define EDITOR_BASE_H

enum {
  local_esc_key   =   27,
  local_enter_key = '\n',  // in WINDOWS / DOS    enter key = 13
};

/* color pairs */

enum {
  main_win_width = 55,
  main_win_height = 18,
};

enum {
  pair_main_win_frame,
  pair_menu_unactive,
  pair_menu_unselected_item,
  pair_menu_selected_item,
};

/* program state */

typedef enum program_state {
  state_quit = 50,
  state_continue,
  state_continue_and_redraw,
} program_state;


#endif
