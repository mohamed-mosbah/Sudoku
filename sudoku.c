#include "sudoku.h"

void start_game_sudoku()
{

    welcome_screen();
    return;

}
static void start_new_game() //creating a new solvable Soduko pattern
{
    // Start measuring time
    time(&begin);
    int i1 ;
    int i2 ;
    char c;
    srand(time(0));
    i1 = rand()%3;
    i2 = rand()%3;
    swap_col(i1, i2);
    swap_row(i1+3,i2+3);
    i1 = rand()%3;
    i2 = rand()%3;
    swap_col(i1+3, i2+3);
    swap_row(i1+6,i2+6);
    i1 = rand()%3;
    i2 = rand()%3;
    swap_col(i1+6,i2+6);
    swap_row(i1,i2);
    i1=rand()%2;
    if(i1)
    {
        array_row__to_col(arr);
    }

    hide_random_values();
    Print_sudoku_array(arr);

    init_user_array();
    while(1)
    {
        add_num_to_grid_interactive();
        flag_reset=0;
        Print_sudoku_array(user_arr);
        if(check_if_sudoku_solved())
            continue;
        break;
    }
    congratulations();
}

static void reset() // deletes all the cells, the user has inputted
{
    init_user_array();
    size_user_entries=0;
    flag_reset=1;
}

static void congratulations()
{
    system("cls");
    time(&end);
    time_t elapsed = end - begin;
    time_t minutes= elapsed/60;
    time_t seconds= elapsed%60;
    printf(G"\n\n\n\tCongratulations."RE" You finished in %ld minutes %ld seconds. \n",minutes,seconds);
    printf("\n\n\nPress an key to go to main screen. \n");
    reset_arr();
    reset();
    getch();
}
static void welcome_screen()
{
    while(1)
    {
        system("cls");
        int action;

        printf(C"\t\t\tWelcome to my Sudoku Game\n\n"RE);
        printf("1: Start new Game\n");
        printf("2: Choose difficulty\n");
        printf("3: How to play\n");
        printf("4: Exit\n");
        printf("\nPlease choose an action by entring the corresponding number(1,2,3,4); ");

        scanf(" %d",&action);
        while((action>4)||(action <1))
        {
            printf("Not a valid entry. Please try again ");
            scanf(" %d",&action);
        }
        if(action==1)
        {
            start_new_game();
        }
        else if(action==2)
        {
            choose_difficulty();
        }
        else if(action==3)
        {
            how_to_play();
        }
        else if(action==4)
        {
            return;
        }
    }

}
static void choose_difficulty()
{
    system("cls");
    printf("Choose the level of difficulty(1,2,3,4):\n");
    printf("1: Easy:\n");
    printf("2: Medium:\n");
    printf("3: Hard:\n");
    printf("4: Master:\n");
    scanf(" %d",&difficulty);
}

static int check_if_sudoku_solved()
{
    int flag_not_solved_yet=0;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(user_arr[i][j]==' ')
                flag_not_solved_yet=1;
        }
    }
    return flag_not_solved_yet;
}


static void add_num_to_grid_interactive()
{
    while(1)
    {


        ask_for_coordinates(&x,&y);
        if(flag_reset==1)
        {
            return;
        }
        c=ask_for_number();

        int ret= check_valid_entry(c,x,y);
        if(ret==NOT_VALID)
        {
            printf("Can't enter %c in (%d,%d)\n",c,x+1,y+1);
            printf("Please try again\n");
            continue;
        }


        user_entries[size_user_entries].x=x;
        user_entries[size_user_entries].y=y;
        size_user_entries++;
        user_arr[x][y]=c;
        return ;
    }
}

static void init_user_array()
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            user_arr[i][j]=arr[i][j];
        }
    }
}

static VALIDITY check_valid_entry(char entry,int row,int col) //check if the entered number is repeated in the same row, column, or subcube
{
    if(arr[row][col]!=' ')
        return NOT_VALID;
    else
    {
        for(int i=0; i<9; i++)
        {
            if(((arr[i][col]+48)==entry)&&(i!=row))
            {
                return NOT_VALID;
            }
        }
        for(int i=0; i<9; i++)
        {
            if(((arr[row][i]+48)==entry)&&(i!=col))
            {
                return NOT_VALID;
            }
        }
        if(!check_valid_in_subcube(entry, row,col))
            return NOT_VALID;
        printf("\n\n%d %d %c\n\n",row+1,col+1,entry);
    }
    return VALID;
}

static void print_struct()
{
    for(int i=0; i<size_user_entries; i++)
    {
        printf("%d %d\n",user_entries[i].x,user_entries[i].y);
    }
}


static void ask_for_coordinates(char*x,char*y)
{
    int i1,i2;
    while(1)
    {
        printf("Please enter the row number for your entry(1,2,3...,9) (0 to Reset): ");
        scanf(" %d",&i1);
        if(i1==0)
        {
            reset();
            return;
        }
        if((i1>9)||(i1<1))
        {
            printf("Not a valid line number.\n");
            continue;
        }
        *x=i1-1;
        break;
    }
    while(1)
    {
        printf("Please enter the column number for your entry(1,2,3...,9): ");
        scanf(" %d",&i2);
        if((i2>9)||(i2<1))
        {
            printf("Not a valid line number.\n");
            continue;
        }
        *y=i2-1;
        break;
    }

}

static char ask_for_number()
{
    char c;
    while(1)
    {
        printf("Please enter a number (1,2,3,....,9): ");
        scanf(" %c",&c);
        if((c>'9')||(c<'1'))
        {
            printf("Not a valid entry. Please try again(1,2,3,....,9): \n");
            continue;
        }
        return c;
    }
}

static void hide_random_values()
{
    int clearboxes=1;
    int j=0;
    for(int z=0; z<clearboxes; z++)
    {
        for(int i=0; i<difficulty; i++)
        {
            j=rand()%9;
            arr[z][j]=' ';
        }
    }
}



static void array_row__to_col(char arr[9][9])
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            helperarr[j][i]=arr[i][j];
        }
    }
    for (int x=0; x<9; x++)
    {
        for (int y=0; y<9; y++)
        {
            arr[x][y] = helperarr[x][y];
        }
    }
}

static void swap_row(int row1, int row2)
{
    char temp;
    for(int i=0; i<9; i++)
    {
        temp=arr[row1][i];
        arr[row1][i]=arr[row2][i];
        arr[row2][i]=temp;
    }
}

static void swap_col(int col1, int col2)
{
    char temp;
    for(int i=0; i<9; i++)
    {
        temp=arr[i][col1];
        arr[i][col1]=arr[i][col2];
        arr[i][col2]=temp;
    }
}



static void Print_sudoku_array(char arr[9][9])
{

    system("cls");
    printf("\n      ");
    for(int i=0; i<9; i++)
    {
        printf(" %d ",i+1);
        if(!((i+1)%3)&&(i<8))
            printf(" ");
    }
    printf("\n\n");
    for(int i=0; i<9; i++)
    {
        printf("  %d:  ",i+1);
        for(int j=0; j<9; j++)
        {
            if((arr[i][j]<10)||((arr[i][j]>48)&&(arr[i][j]<59)))
            {
                int returned = check_if_user_input(i,j);
                if(returned) //printing in Green if this is a cell filled by the user
                {
                    printf(G" %c "RE, arr[i][j]);
                }
                else
                {
                    printf(" %c ", arr[i][j]+48);
                }
            }

            else
                printf(" %c ", arr[i][j]);
            if(!((j+1)%3)&&(j<8))
                printf("|");
        }
        if((i+1)%3)
            printf("\n");
        else if((i<8)&&(!((i+1)%3)))
            printf("\n       ---------------------------\n");
    }
    printf("\n\n\n");
}

static VALIDITY check_if_user_input(int num1,int num2)
{

    for(int i=0; i<size_user_entries; i++)
    {
        if((user_entries[i].x==num1)&&(user_entries[i].y==num2))
            return VALID;
    }
    return NOT_VALID;
}

static VALIDITY check_valid_in_subcube(char possible_entry, int row,int col)
{
    row= (row/3)*3;
    col= (col/3)*3;
    for(int i=row; i<row+3; i++)
    {

        for(int j=col; j<col+3; j++)
        {
            if((possible_entry==arr[i][j])||(possible_entry==user_arr[i][j]))
                return NOT_VALID;
        }
    }
    return VALID;
}


static void how_to_play()
{
    char pseudo;
    system("cls");
    printf(C"Rule 1"RE" - Each row must contain the numbers from 1 to 9, without repetitions\n");
    printf(C"Rule 2"RE" - Each column must contain the numbers from 1 to 9, without repetitions\n");
    printf(C"Rule 3"RE" - The digits can only occur once per block\n");

    printf("\n\nPress any key to go to the main screen");
    getch();
}


static void reset_arr() //
{
    for (int x=0; x<9; x++)
    {
        for (int y=0; y<9; y++)
        {
            arr[x][y] = helperarr[x][y];
        }
    }
}
