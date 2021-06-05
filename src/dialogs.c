/**/

#include <ncurses.h>

#include "ncurs_ext.h"
#include "editor_base.h"
#include "draws.h"
#include "dialogs.h"

const scr_point main_menu_start = { 0, 5 };

const submenu_info file_submenu_info = {
  {1, 5}, 4, 20
};

const submenu_info edit_submenu_info = {
  {1, 18}, 5, 20
};

const submenu_info misc_submenu_info = {
  {1, 30}, 2, 20
};

const menu_item editor_main_menu_data[] = {
  { "    File     ", "Save, load etc...",      state_file_submenu },
  { "    Edit    ", "Level manipulations",    state_edit_submenu },
  { "    Misc.    ", "Miscellanious options" , state_misc_submenu }
};

const menu_item file_submenu_data[] = {
  { "New      ", "Create a NEW level file",      state_file_submenu },
  { "Load     ", "Load a level file",      state_file_submenu },
  { "Save     ", "Save current level file",    state_edit_submenu },
  { "Exit     ", "Exit" , state_misc_submenu }

};
const menu_item edit_submenu_data[] = {
  { "Cut       ", "Cut level and move to clipboard",      state_file_submenu },
  { "Copy      ", "Copy level to clipboard",    state_edit_submenu },
  { "Insert    ", "Insert current level from clipboard" , state_misc_submenu },
  { "Replace   ", "Replace current level from clipboard",      state_file_submenu },
  { "Clipboard ", "Show clipboard",  state_file_submenu },
  
};
const menu_item misc_submenu_data[] = {
  { "Help      ", "Show HELP screen",      state_file_submenu },
  { "About     ", "Show ABOUT screen    ",    state_edit_submenu },
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
  while (current_pos <= editor_main_menu_max )
  {
    if (current_pos != position)
      attrset(COLOR_PAIR(pair_menu_item_unselected) | A_BOLD);
    else
      attrset(COLOR_PAIR(pair_menu_item_selected) | A_NORMAL);
    printw(main_menu[current_pos].caption);
    current_pos++;
  }
#ifdef DEBUG
  attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL );
  printw("%d", position);
#endif   
}

program_state select_submenu(WINDOW* main_win, program_state main_menu_state)
{
  switch (main_menu_state) {
    case state_file_submenu: {
    	 return submenu(file_submenu_info, file_submenu_data, main_win);
       break;  
    }
    case state_edit_submenu: {
  	    return submenu(edit_submenu_info, edit_submenu_data, main_win);
       break;
    }
    case state_misc_submenu: {
      return submenu(misc_submenu_info, misc_submenu_data, main_win);
      break;  
    } 
  } /* switch (main_menu_state) */
  return state_continue;
}

program_state submenu(const submenu_info info, const menu_item submenu[], WINDOW* main_win)
{
  int submenu_win_width, submenu_win_height;
  	
  WINDOW* submenu_win;
  submenu_win_height = info.count + 2;
  submenu_win_width  = info.width + 2;
  
  submenu_win = newwin(submenu_win_height, submenu_win_width, info.submenu_ltop.row, info.submenu_ltop.col);
  wbkgd(submenu_win, COLOR_PAIR(pair_menu_item_unselected));
  wdraw_frame(submenu_win, submenu_win_height, submenu_win_width, zero_point, show_frame);
  wrefresh(stdscr);
  touchwin(main_win);
  wrefresh(submenu_win);
  napms(3000);
  delwin(submenu_win);
  return state_continue;
}

program_state main_menu(editor_obj_coords* coords,
                        WINDOW* main_win,
                        int main_menu_max,
                        const menu_item main_menu[])
{
  chtype sym;
  int pos = 0;
  program_state tmp_state = state_continue;
  
  show_active_main_menu(pos, main_menu_max, main_menu);
  touchwin(main_win);
  wrefresh(stdscr);
  keypad(stdscr, TRUE);
  for(;;)
  {
    sym = wgetch(stdscr);
    switch (sym)
    {
       case KEY_RESIZE:
       {
          editor_redraw(main_win, coords, no_draw_main_menu);
          show_active_main_menu(pos, main_menu_max, main_menu);
          touchwin(main_win);
          wrefresh(stdscr);
          break;
       }
       case KEY_LEFT: /* <<< */
       {
          if (pos > 0)
          {
          	pos--;
            show_active_main_menu(pos, main_menu_max, main_menu);
            touchwin(main_win);
            wrefresh(stdscr);
          }  
          break;
       }
       case KEY_RIGHT: /* >>> */
       {
          if (pos < main_menu_max )
          {
          	pos++;
            show_active_main_menu(pos, main_menu_max, main_menu);
            touchwin(main_win);
            wrefresh(stdscr);
          }  
          break;
       }
       case KEY_DOWN:
       {
          tmp_state = select_submenu(main_win, main_menu[pos].state);
          return tmp_state;
       }
    }   /* switch (sym) */
  }     /* for(;;)      */
  show_unactive_main_menu(editor_main_menu_max, editor_main_menu_data);
  touchwin(main_win);
  wrefresh(stdscr);
  return tmp_state;
}