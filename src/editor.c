/*

*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_base.h"
#include "ncurs_ext.h"
#include "draws.h"
#include "dialogs.h"
#include "main_win.h"
#include "editor.h"

program_condition init_program_condition()
{
  program_condition tmp;
  calculate_obj_coords(&tmp, NULL);
  tmp.main_menu_pos = main_menu_unactive;
  tmp.second_win_state = second_win_is_other;
  return tmp;
}

void editor_init()
{
  initscr();
  if ( !has_colors() ) {
    fprintf(stderr, "Terminal not supports COLORS !\n");
    exit(1);
  }
  if ( start_color() != OK ) {
    fprintf(stderr, "Unable to start COLORS !\n");
    exit(2);
  }
  init_all_colors();
  crmode();
  noecho();
}

void editor_done()
{
  endwin();
  printf("Thanks for using S_BAHN_ED editor !\n");
  exit(EXIT_SUCCESS);
}

void editor_run()
{
  WINDOW* main_win;
  chtype sym;
  program_event event = ev_continue;
  program_condition condition;

  condition = init_program_condition();
  main_win = newwin(main_win_height,
                    main_win_width,
                    condition.begin_main_win.row,
                    condition.begin_main_win.col );
  draw_main_win_statics(main_win);
  editor_redraw(&condition, main_win, NULL);
  keypad(main_win, TRUE);

/* MAIN CYCLE */

  for(;;) {
    sym = wgetch(main_win);
    switch (sym) {
      case KEY_RESIZE: {
        editor_redraw(&condition, main_win, NULL);
        break;
      }
      case KEY_F(10): {
        event = main_menu(&condition,
                          main_win,
                          editor_main_menu_max,
                          editor_main_menu_data);
        editor_redraw(&condition, main_win, NULL);
        break;
      }
      case KEY_F(12): {
        editor_done();
      }
    } /* switch (sym) */
  }
}