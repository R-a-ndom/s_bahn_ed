#include <ncurses.h>

#include "ncurs_ext.h"
#include "editor_base.h"
#include "dialogs.h"
#include "draws.h"

void init_all_colors()
{
  init_pair(pair_standard, COLOR_WHITE, COLOR_BLACK);
  init_pair(pair_main_win_standard, COLOR_BLACK, COLOR_CYAN);

  init_pair(pair_menu_unactive, COLOR_BLACK, COLOR_WHITE);
  init_pair(pair_menu_item_unselected, COLOR_MAGENTA, COLOR_WHITE);
  init_pair(pair_menu_item_selected, COLOR_BLUE, COLOR_BLACK);

  init_pair(pair_empty, COLOR_WHITE,  COLOR_BLACK);
  init_pair(pair_wall, COLOR_WHITE, COLOR_YELLOW);
  init_pair(pair_box, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(pair_player, COLOR_WHITE, COLOR_GREEN);

  init_pair(pair_empty_cursor, COLOR_RED, COLOR_BLACK);
  init_pair(pair_wall_cursor, COLOR_RED, COLOR_YELLOW);
  init_pair(pair_box_cursor, COLOR_RED, COLOR_MAGENTA);
  init_pair(pair_player_cursor, COLOR_RED, COLOR_GREEN);
}

void calculate_obj_coords(program_condition* condition, WINDOW* second_win)
{
  scr_point tmp_stdscr_size, tmp_size_second_win;

  getmaxyx(stdscr, condition->screen_size.row, condition->screen_size.col);
  tmp_stdscr_size = get_middle();
  condition->begin_main_win.row =
      tmp_stdscr_size.row - ( main_win_height / 2 );
  condition->begin_main_win.col =
      tmp_stdscr_size.col - ( main_win_width  / 2 );
  if (second_win) {
    getmaxyx(second_win,
             tmp_size_second_win.row,
             tmp_size_second_win.col);
      if (condition->second_win_state != second_win_is_submenu) {
        condition->begin_second_win.row = tmp_stdscr_size.row - ( tmp_size_second_win.row / 2 );
        condition->begin_second_win.col = tmp_stdscr_size.col - ( tmp_size_second_win.col / 2 );
    } else {
      getbegyx(second_win,
               condition->begin_second_win.row,
               condition->begin_second_win.col);
    }
  } else {
    condition->begin_second_win = zero_point;
  }
}

void draw_stdscr_statics(program_condition* condition)
{
  int current_col = 0;
  attrset(COLOR_PAIR(pair_standard) | A_NORMAL);
  while (current_col < condition->screen_size.col) {
    move(1, current_col);
    addch('-');
    move(condition->screen_size.row - 2, current_col);
    addch('-');
    current_col++;
  }
  current_col = 0;
  attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL);
  move(0, 0);
  while (current_col < condition->screen_size.col) {
    addch(' ');
    current_col++;
  }
}

void editor_redraw(program_condition* condition, WINDOW* main_win, WINDOW* second_win)
{
  erase();
  calculate_obj_coords(condition, second_win);
  draw_stdscr_statics(condition);
  show_main_menu(editor_main_menu_max, editor_main_menu_data, condition->main_menu_pos);
  mvwin(main_win,
        condition->begin_main_win.row, condition->begin_main_win.col);
  if (second_win) {
    touchwin(second_win);
    if (condition->second_win_state != second_win_is_submenu) {
      mvwin(second_win,
            condition->begin_second_win.row, condition->begin_second_win.col);
    }
  }
  wrefresh(stdscr);
  wrefresh(main_win);
  if (second_win)
    wrefresh(second_win);
}