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
  while ( i < info.max ) {
    wmove(submenu_win, i+1, 1);
    if (i == current_pos)
      wattrset(submenu_win, COLOR_PAIR(pair_menu_item_selected) | A_BOLD);
    else
      wattrset(submenu_win, COLOR_PAIR(pair_menu_item_unselected) | A_NORMAL);
    wprintw(submenu_win, submenu[i].caption);
    i++;
  }
}

#ifdef DEBUG
static void debug_print_submenu_pos(WINDOW* submenu_win, int pos)
{
  wattrset(submenu_win, COLOR_PAIR(pair_menu_item_unselected) | A_NORMAL);
  wmove(submenu_win, 0,0);
  wprintw(submenu_win, "%d", pos); 
}
#endif          


program_event submenu_action(program_condition* condition,
                             const submenu_info info,
                             const menu_item submenu[],
                             WINDOW* main_win)
{
  int submenu_win_width, submenu_win_height;
  WINDOW* submenu_win;
  int current_pos = 0;
  chtype sym;
  program_event tmp_event = ev_continue;
  
  submenu_win_height = info.max + 2;
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
#ifdef DEBUG
  debug_print_submenu_pos(submenu_win, current_pos);
#endif
  wrefresh(stdscr);
  touchwin(main_win);
  wrefresh(submenu_win);
  keypad(submenu_win, TRUE);
  do {
    sym = wgetch(submenu_win);
    switch (sym) {
      case KEY_RESIZE: {
      	editor_redraw(condition, main_win, submenu_win);
         break;             
      }    
      case KEY_UP: {
        if (current_pos > 0) {
          current_pos--;
          show_submenu(submenu_win, current_pos, info, submenu);
#ifdef DEBUG
          debug_print_submenu_pos(submenu_win, current_pos);
#endif
          wrefresh(submenu_win);
        }
        break;
      }
      case KEY_DOWN: {
        if (current_pos < info.max - 1) {
          current_pos++;
          show_submenu(submenu_win, current_pos, info, submenu);
#ifdef DEBUG
          debug_print_submenu_pos(submenu_win, current_pos);
#endif
          wrefresh(submenu_win);
        }      	
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

program_event submenu(program_condition* condition, WINDOW* main_win, program_event main_menu_event)
{
  condition->second_win_state = second_win_is_submenu;	
  switch (main_menu_event) {
    case ev_file_submenu: {
    	 return submenu_action(condition, file_submenu_info, file_submenu_data, main_win);
       break;  
    }
    case ev_edit_submenu: {
  	    return submenu_action(condition, edit_submenu_info, edit_submenu_data, main_win);
       break;
    }
    case ev_misc_submenu: {
      return submenu_action(condition, misc_submenu_info, misc_submenu_data, main_win);
      break;  
    } 
  } /* switch (main_menu_state) */
  condition->second_win_state = second_win_is_other;	
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
  do {
    sym = wgetch(stdscr);
    switch (sym)
    {
       case KEY_RESIZE: {
       	condition->main_menu_pos = pos;
         editor_redraw(condition, main_win, NULL);
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
       case local_esc_key: {
         tmp_event = ev_exit_from_menu;
         break;       
       }
       case KEY_DOWN: {
         condition->main_menu_pos = pos;
         tmp_event = submenu(condition, main_win, main_menu[pos].action);
         break;
       }
    }   /* switch (sym) */
  } while (tmp_event == ev_continue); /* DO {} WHILE */
  condition->main_menu_pos = main_menu_unactive;
  editor_redraw(condition, main_win, NULL);
  return tmp_event;
}