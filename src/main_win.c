/**/

#include <ncurses.h>

#include "ncurs_ext.h"
#include "editor_base.h"
#include "main_win.h"

void draw_main_win_statics(WINDOW* main_win)
{
  wattrset(main_win, COLOR_PAIR(pair_selected));
  wdraw_frame(main_win,
              main_win_height, main_win_width,
              zero_point,
              show_frame);
}