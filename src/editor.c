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


void editor_init()
{
  initscr();
  if ( !has_colors() )
  {
    fprintf(stderr, "Terminal not supports COLORS !\n");
    exit(1);
  }
  if ( start_color() != OK )
  {
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
  editor_obj_coords main_coords;
  chtype sym;
  program_state state = state_continue;
  calculate_obj_coords(&main_coords);
  main_win = newwin(main_win_height,
                    main_win_width,
                    main_coords.coords_main_win.row,
                    main_coords.coords_main_win.col );
  draw_main_win_statics(main_win);
  editor_redraw(main_win, &main_coords, draw_main_menu);
  keypad(main_win, TRUE);

/* MAIN CYCLE */

  for(;;)
  {
    sym = wgetch(main_win);
    switch (sym)
    {
      case KEY_RESIZE:
      {
        editor_redraw(main_win, &main_coords, draw_main_menu);
        break;
      }
      case KEY_F(10):
      {
        state = main_menu(&main_coords,
                          main_win,
                          editor_main_menu_max,
                          editor_main_menu);
        editor_redraw(main_win, &main_coords, draw_main_menu);
        break;
      }
      case KEY_F(12):
      {
        editor_done();
      }
    } /* switch (sym) */
  }
}