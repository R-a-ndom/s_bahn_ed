/**/

#include <ncurses.h>

#include "ncurs_ext.h"
#include "editor_base.h"

#include "dialogs.h"

const scr_point main_menu_start = { 0, 5 };

const menu_item editor_main_menu[] = {
  { " [   File    ] ", "Save, load etc...",      state_file_submenu },
  { " [   Level   ] ", "Level manipulations",    state_level_submenu },
  { " [   Misc.   ] ", "Miscellanious options" , state_misc_submenu }
};

void show_unactive_main_menu(int main_menu_max,
                             const menu_item main_menu[])
{
  int current_pos = 0;
  move(main_menu_start.row, main_menu_start.col);
  attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL);
  while (current_pos <= editor_main_menu_max)
  {
    printw(main_menu[current_pos].caption);
    current_pos++;
  }
}

void show_active_main_menu(int position,
                           int main_menu_max,
                           const menu_item main_menu[])
{
  int current_pos = 0;
  move(main_menu_start.row, main_menu_start.col);
  while (current_pos <= editor_main_menu_max)
  {
    if (current_pos != position)
      attrset(COLOR_PAIR(pair_menu_item_unselected) | A_BOLD);
    else
      attrset(COLOR_PAIR(pair_menu_item_selected) | A_NORMAL);
    printw(main_menu[current_pos].caption);
    current_pos++;
  }
}

program_state main_menu(editor_obj_coords* coords,
                        WINDOW* main_win,
                        int main_menu_max,
                        const menu_item main_menu[])
{
  int pos = 0;
  show_active_main_menu(pos, main_menu_max, main_menu);
  touchwin(main_win);
  wrefresh(stdscr);
  napms(debug_delay);
  return state_continue;
}