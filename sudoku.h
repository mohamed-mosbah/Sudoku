#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R     "\x1b[31m"
#define G   "\x1b[32m"
#define Y  "\x1b[33m"
#define B    "\x1b[34m"
#define M "\x1b[35m"
#define C   "\x1b[36m"
#define RE   "\x1b[0m"
#include <time.h>

typedef enum Valid_status
{
    VALID = 1,
    NOT_VALID = 0,
} VALIDITY;

void start_game_sudoku();
static void Print_sudoku_array(char arr[9][9]);
static char create_valid_entry(char row,char col);
static VALIDITY check_valid_entry(char entry,int row,int col);
static VALIDITY check_valid_in_subcube(char possible_entry, int row,int col);
static void init_array();
static void reverse_array_horizontal();
static void reverse_array_vertical();
static void array_row__to_col(char arr[9][9]);
static void swap_row(int row1, int row2);
static void swap_col(int col1, int col2);
static void hide_random_values();
static char ask_for_number();
static void clean_user_array();
static void finished();
static int check_if_sudoku_solved();
static VALIDITY check_if_user_input(int i,int j);
static int flag_reset;
static void congratulations();
static void welcome_screen();
static void choose_difficulty();
static void add_num_to_grid_interactive();
static void init_user_array();
static void ask_for_coordinates(char*x,char*y);
static void how_to_play();
static char user_arr[9][9];
static int difficulty=1;

struct coordinates
{
    int x;
    int y;
};
struct coordinates user_entries[36];
static int size_user_entries=0;


static char arr[9][9]=        {{5,3,4,6,7,8,9,1,2},
    {6,7,2,1,9,5,3,4,8},
    {1,9,8,3,4,2,5,6,7},
    {8,5,9,7,6,1,4,2,3},
    {4,2,6,8,5,3,7,9,1},
    {7,1,3,9,2,4,8,5,6},
    {9,6,1,5,3,7,2,8,4},
    {2,8,7,4,1,9,6,3,5},
    {3,4,5,2,8,6,1,7,9}
};

static char helperarr[9][9]=  {{1,2,3,4,5,6,7,8,9},
    {4,5,6,7,8,9,1,2,3},
    {7,8,9,1,2,3,4,5,6},
    {2,3,1,5,6,4,8,9,7},
    {5,6,4,8,9,7,2,3,1},
    {8,9,7,2,3,1,5,6,4},
    {3,1,2,6,4,5,9,7,8},
    {6,4,5,9,7,8,3,1,2},
    {9,7,8,3,1,2,6,4,5}
};
static int x;
static int y;
static char c;
time_t begin, end;

#endif // SUDOKU_H_INCLUDED
