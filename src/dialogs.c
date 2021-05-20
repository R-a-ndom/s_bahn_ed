/**/

#include <ncurses.h>

#include "ncurs_ext.h"
#include "editor_base.h"

#include "dialogs.h"

const scr_point main_menu_start = { 0, 5 };

const menu_item editor_main_menu[] = {
  { "[   File    ]", "Save, load etc...",      state_file_submenu },
  { "[   Level   ]", "Level manipulations",    state_level_submenu },
  { "[   Misc.   ]", "Miscellanious options" , state_misc_submenu }
};

void show_unactive_main_menu(int main_menu_max, const menu_item main_menu[])
{
  int current_pos = 0;
  move(0, 0);
  attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL);
  while (current_pos <= editor_main_menu_max)
  {
    printw(main_menu[current_pos].caption);
    addch(' ');
    current_pos++;
  }
}