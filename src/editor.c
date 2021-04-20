/*

*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_base.h"
#include "ncurs_ext.h"
#include "main_win.h"
#include "editor.h"

void init_all_colors()
{
  init_pair(pair_standard, COLOR_WHITE, COLOR_BLACK);
  init_pair(pair_selected, COLOR_YELLOW, COLOR_BLACK);
  init_pair(pair_menu_unactive, COLOR_WHITE, COLOR_BLACK);
  init_pair(pair_menu_item_non_sel, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(pair_menu_item_sel, COLOR_WHITE, COLOR_YELLOW);
}

void draw_stdscr_statics(editor_obj_coords* coords)
{
  int current_col = 0;
  addstr("S_BAHN level editor!");
  while (current_col < coords->screen_size.col)
  {
    move(1, current_col);
    addch('-');
    current_col++;
  }
}

void calculate_obj_coords(editor_obj_coords* coords)
{
  scr_point tmp_scr_size;

  getmaxyx(stdscr, coords->screen_size.row, coords->screen_size.col);
  tmp_scr_size = get_middle();
  coords->coords_main_win.row =
      tmp_scr_size.row - ( main_win_height / 2 );
  coords->coords_main_win.col =
      tmp_scr_size.col - ( main_win_width  / 2 );
}

void editor_redraw(WINDOW* main_win, editor_obj_coords* coords)
{
  erase();
  calculate_obj_coords(coords);
  draw_stdscr_statics(coords);
  mvwin(main_win, coords->coords_main_win.row, coords->coords_main_win.col);
  wrefresh(stdscr);
  wrefresh(main_win);
}

void editor_init()
{
  initscr();
  if ( !has_colors() )
  {
    printf("Terminat not supports COLORS !\n");
    exit(1);
  }
  if ( start_color() != OK )
  {
    printf("Unable to start COLORS !\n");
    exit(2);
  }
  init_all_colors();
  crmode();
  noecho();
}

void editor_run()
{
  WINDOW* main_win;
  editor_obj_coords main_coords;
  chtype sym;

  calculate_obj_coords(&main_coords);
  main_win = newwin(main_win_height,
                    main_win_width,
                    main_coords.coords_main_win.row,
                    main_coords.coords_main_win.col );
  draw_stdscr_statics(&main_coords);
  draw_main_win_statics(main_win);
  wrefresh(stdscr);
  wrefresh(main_win);
  keypad(main_win, TRUE);
  for(;;)
  {
    sym = wgetch(main_win);
    switch (sym)
    {
      case KEY_RESIZE:
      {
        editor_redraw(main_win, &main_coords);
        break;
      }
      case KEY_F(10):
      {
        endwin();
        printf("Thanks for using S_BAHN_ED editor !\n");
        exit(EXIT_SUCCESS);
      }
    } /* switch (sym) */
  }
}