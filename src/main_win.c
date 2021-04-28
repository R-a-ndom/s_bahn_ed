/**/

#include <ncurses.h>

#include "ncurs_ext.h"
#include "editor_base.h"
#include "main_win.h"

void draw_main_win_statics(WINDOW* main_win)
{
  wbkgd(main_win, COLOR_PAIR(pair_main_win_standard));
  wdraw_frame(main_win,
              main_win_height, main_win_width,
              zero_point,
              show_frame);
}