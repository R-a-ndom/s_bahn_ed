/*

*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_base.h"
#include "ncurs_ext.h"
#include "dialogs.h"
#include "main_win.h"
#include "editor.h"

void init_all_colors()
{
  init_pair(pair_standard, COLOR_WHITE, COLOR_BLACK);
  init_pair(pair_main_win_standard, COLOR_BLACK, COLOR_WHITE);

  init_pair(pair_menu_unactive, COLOR_BLACK, COLOR_WHITE);
  init_pair(pair_menu_item_non_sel, COLOR_MAGENTA, COLOR_WHITE);
  init_pair(pair_menu_item_sel, COLOR_YELLOW, COLOR_WHITE);

  init_pair(pair_empty, COLOR_WHITE,  COLOR_BLACK);
  init_pair(pair_wall, COLOR_WHITE, COLOR_YELLOW);
  init_pair(pair_box, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(pair_player, COLOR_WHITE, COLOR_GREEN);

  init_pair(pair_empty_cursor, COLOR_RED, COLOR_BLACK);
  init_pair(pair_wall_cursor, COLOR_RED, COLOR_YELLOW);
  init_pair(pair_box_cursor, COLOR_RED, COLOR_MAGENTA);
  init_pair(pair_player_cursor, COLOR_RED, COLOR_GREEN);
}

void draw_stdscr_statics(editor_obj_coords* coords)
{
  int current_col = 0;
  attrset(COLOR_PAIR(pair_standard) | A_NORMAL);
  while (current_col < coords->screen_size.col)
  {
    move(1, current_col);
    addch('-');
    move(coords->screen_size.row - 2, current_col);
    addch('-');
    current_col++;
  }
  current_col = 0;
  attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL);
  move(0, 0);
  while (current_col < coords->screen_size.col)
  {
    addch(' ');
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
  show_unactive_main_menu(editor_main_menu_max, editor_main_menu);
  mvwin(main_win,
        coords->coords_main_win.row, coords->coords_main_win.col);
  wrefresh(stdscr);
  wrefresh(main_win);
}

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

  calculate_obj_coords(&main_coords);
  main_win = newwin(main_win_height,
                    main_win_width,
                    main_coords.coords_main_win.row,
                    main_coords.coords_main_win.col );
  draw_stdscr_statics(&main_coords);
  draw_main_win_statics(main_win);
  editor_redraw(main_win, &main_coords);
  wrefresh(stdscr);
  wrefresh(main_win);
  keypad(main_win, TRUE);

/* MAIN CYCLE */

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
        editor_done();
      }
    } /* switch (sym) */
  }
}