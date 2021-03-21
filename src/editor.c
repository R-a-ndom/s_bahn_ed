/*

*/

#include <ncurses.h>

#include "editor_base.h"
#include "ncurs_ext.h"
#include "main_win.h"
#include "editor.h"

void draw_stdscr_statics()
{
  scr_point scr_size;
  int current_col = 0;
  getmaxyx(stdscr, scr_size.row, scr_size.col);
  addstr("S_BAHN level editor!");
  while (current_col < scr_size.col)
  {
    move(1, current_col);
    addch('-');
    current_col++;
  }
}

editor_obj_coords calculate_obj_coords()
{
  editor_obj_coords tmp_coords;

  tmp_coords.screen_size = get_middle();
  tmp_coords.coords_main_win.row =
      tmp_coords.screen_size.row - ( main_win_height / 2 );
  tmp_coords.coords_main_win.col =
      tmp_coords.screen_size.col - ( main_win_width  / 2 );
  return tmp_coords;
}

void editor_init()
{
  initscr();
}

void editor_run()
{
  WINDOW* main_win;
  editor_obj_coords main_coords;

  main_coords = calculate_obj_coords();
  main_win = newwin(main_win_height,
                    main_win_width,
                    main_coords.coords_main_win.row,
                    main_coords.coords_main_win.col );
  draw_stdscr_statics();
  draw_main_win_statics(main_win);
  wrefresh(stdscr);
  wrefresh(main_win);
  napms(3000);
  endwin();
}