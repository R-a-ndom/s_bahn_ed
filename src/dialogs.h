/**/

#ifndef DIALOGS_H
#define DIALOGS_H

enum {
  editor_main_menu_max = 2,
};

enum {
  menu_caption_max = 20,
  menu_hint_max    = 50,
};

typedef struct menu_item {
  char caption[menu_caption_max];
  char hint[menu_hint_max];
  program_state state;
} menu_item;

typedef struct submenu_info {
  scr_point submenu_ltop;
  int count;
  int width;
} submenu_info;

extern const scr_point main_menu_start;

extern const menu_item editor_main_menu_data[];

/*  ---  ++++  ----  */

void show_unactive_main_menu(int main_menu_max,
                             const menu_item main_menu[]);

void show_active_main_menu(int position,
                           int main_menu_max,
                           const menu_item main_menu[]);
                           
program_state select_submenu(WINDOW* main_win, program_state main_menu_state);

program_state submenu(const submenu_info info, const menu_item submenu[], WINDOW* main_win);

program_state main_menu(editor_obj_coords* coords,
                        WINDOW* main_win,
                        int main_menu_max,
                        const menu_item main_menu[]);


#endif