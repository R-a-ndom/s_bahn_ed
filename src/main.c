/*
  S_BAHN - console *NIX Sokoban clone
  written on C using NCURSES
  levels editor

  editor.c - levels editor main file
*/

#include <ncurses.h>
#include <unistd.h>

#include "editor_base.h"
#include "ncurs_ext.h"
#include "dialogs.h"
#include "main_win.h"
#include "editor.h"

int main(int argc, char *argv[])
{
  editor_init();
  editor_run();
  return 0;
}