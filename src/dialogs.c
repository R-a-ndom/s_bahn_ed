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
  {1, 31}, 2, 20
};

const menu_item editor_main_menu_data[] = {
  { "    File     ", "Save, load etc...", ev_file_submenu },
  { "    Edit     ", "Level manipulations", ev_edit_submenu },
  { "    Misc.    ", "Miscellanious options" , ev_misc_submenu }
};

const menu_item file_submenu_data[] = {
  { "New      ", "Create a NEW level file",  ev_file_submenu },
  { "Load     ", "Load a level file", ev_file_submenu },
  { "Save     ", "Save current level file", ev_edit_submenu },
  { "Exit     ", "Exit from editor" , ev_misc_submenu }

};
const menu_item edit_submenu_data[] = {
  { "Cut       ", "Cut level and move to clipboard",  ev_file_submenu },
  { "Copy      ", "Copy level to clipboard",  ev_edit_submenu },
  { "Insert    ", "Insert current level from clipboard" , ev_misc_submenu },
  { "Replace   ", "Replace current level from clipboard", ev_file_submenu },
  { "Clipboard ", "Show clipboard",  ev_file_submenu },
  
};
const menu_item misc_submenu_data[] = {
  { "Help      ", "Show HELP screen",  ev_file_submenu },
  { "About     ", "Show ABOUT screen",  ev_edit_submenu },
};


void show_main_menu(int main_menu_max,
                    const menu_item main_menu[],
                    int position)
{
  int current_pos = 0;
  move(main_menu_start.row, main_menu_start.col);
  if ( position == main_menu_unactive) {
    attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL);
    while (current_pos <= editor_main_menu_max) {
      printw(main_menu[current_pos].caption);
      current_pos++;
    }
  } else {
    while (current_pos <= editor_main_menu_max ) {
      if (current_pos == position)
        attrset(COLOR_PAIR(pair_menu_item_selected) | A_BOLD);
      else
        attrset(COLOR_PAIR(pair_menu_item_unselected) | A_NORMAL);
      printw(main_menu[current_pos].caption);
      current_pos++;
    }
#ifdef DEBUG
  attrset(COLOR_PAIR(pair_menu_unactive) | A_NORMAL );
  printw("  %d", position);
#endif   
  }
}


static void show_submenu(WINDOW* submenu_win,
                         const int current_pos,
                         const submenu_info info,
                         const menu_item submenu[])
{
  int i = 0;
  while ( i < info.count ) {
    wmove(submenu_win, i+1, 1);
    if (i == current_pos)
      wattrset(submenu_win, COLOR_PAIR(pair_menu_item_selected) | A_BOLD);
    else
      wattrset(submenu_win, COLOR_PAIR(pair_menu_item_unselected) | A_NORMAL);
    wprintw(submenu_win, submenu[i].caption);
    i++;
  }
}

program_event submenu_action(const submenu_info info,
                             const menu_item submenu[],
                             WINDOW* main_win)
{
  int submenu_win_width, submenu_win_height;
  WINDOW* submenu_win;
  int current_pos = 0;
  chtype sym;
  program_event tmp_event = ev_continue;
  
  submenu_win_height = info.count + 2;
  submenu_win_width  = info.width + 2;
  
  submenu_win = newwin(submenu_win_height,
                       submenu_win_width,
                       info.submenu_ltop.row,
                       info.submenu_ltop.col);
  wbkgd(submenu_win, COLOR_PAIR(pair_menu_item_unselected));
  wdraw_frame(submenu_win,
              submenu_win_height, submenu_win_width,
              zero_point,
              show_frame);
  show_submenu(submenu_win, current_pos, info, submenu);
  wrefresh(stdscr);
  touchwin(main_win);
  wrefresh(submenu_win);
  keypad(submenu_win, TRUE);
  do {
    sym = wgetch(submenu_win);
    switch (sym) {
      case KEY_RESIZE: {
         break;             
      }    
      case KEY_UP: {
         break;
      }
      case KEY_DOWN: {
         break;
      }
      case local_esc_key: {
         break;
      }
      case local_enter_key: {
         break;
      }
    } /* switch (sym) */  
  } while ((sym  != local_esc_key  ) && 
           ( sym != local_enter_key)); /* do - while */
  delwin(submenu_win);
  return tmp_event;
}

program_event submenu(WINDOW* main_win, program_event main_menu_event)
{
  switch (main_menu_event) {
    case ev_file_submenu: {
    	 return submenu_action(file_submenu_info, file_submenu_data, main_win);
       break;  
    }
    case ev_edit_submenu: {
  	    return submenu_action(edit_submenu_info, edit_submenu_data, main_win);
       break;
    }
    case ev_misc_submenu: {
      return submenu_action(misc_submenu_info, misc_submenu_data, main_win);
      break;  
    } 
  } /* switch (main_menu_state) */
  return ev_continue;
}


program_event main_menu(program_condition* condition,
                        WINDOW* main_win,
                        int main_menu_max,
                        const menu_item main_menu[])
{
  chtype sym;
  int pos = 0;
  program_event tmp_event = ev_continue;
  
  show_main_menu(main_menu_max, main_menu, pos);
  touchwin(main_win);
  wrefresh(stdscr);
  keypad(stdscr, TRUE);
  for(;;) {
    sym = wgetch(stdscr);
    switch (sym)
    {
       case KEY_RESIZE: {
         editor_redraw(main_win, NULL, condition);
         touchwin(main_win);
         wrefresh(stdscr);
         break;
       }
       case KEY_LEFT: { /* <<< */
         if (pos > 0) {
           pos--;
           show_main_menu(main_menu_max, main_menu, pos);
           touchwin(main_win);
           wrefresh(stdscr);
         }  
         break;
       }
       case KEY_RIGHT: { /* >>> */
         if (pos < main_menu_max ) {
           pos++;
           show_main_menu(main_menu_max, main_menu, pos);
           touchwin(main_win);
           wrefresh(stdscr);
         }  
         break;
       }
       case KEY_DOWN: {
         tmp_event = submenu(main_win, main_menu[pos].action);
         return tmp_event;
       }
    }   /* switch (sym) */
  }     /* for(;;)      */
  show_main_menu(editor_main_menu_max,
                 editor_main_menu_data,
                 main_menu_unactive);
  touchwin(main_win);
  wrefresh(stdscr);
  return tmp_event;
}