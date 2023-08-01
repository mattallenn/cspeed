#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>


#define NUM_WORDS 25
#define TEXT_WIDTH 36
#define TEXT_HEIGHT 5
int main() 
{


    char result[NUM_WORDS * 15]; //Array of all characters of selected words
    int result_index = 0;
    int cursor_index = 0;
    char input;

    initscr(); //Starts Curses
    cbreak(); //Disables line buffering
    noecho(); //Disables echoing of characters

    //Gets size of terminal to center text
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int text_width = TEXT_WIDTH;
    int text_height = TEXT_HEIGHT;
    int row = (max_y / 2) - (text_height / 2);
    int col = (max_x / 2) - (text_width / 2);
    
    move(row, col); //Moves cursor to center of screen
    printw("%d\n", row);
    printw("%d", col);
    printw(
    "                                 __ \n"
    ".----.-----.-----.-----.-----.--|  |\n"
    "|  __|__ --|  _  |  -__|  -__|  _  |\n"
    "|____|_____|   __|_____|_____|_____|\n"
     "          |__|                        ");
    
    refresh(); //Refreshes screen to show text
               
    //Opens file 
    FILE* file = fopen("1-1000.txt", "r");
    if (file == NULL) {
    
        printf("Error opening file\n");
        exit(1);
    }

    // Creates 2d array, num_lines is a row, maxchar is the array or chars to make a string
    char lines[500][12];
    int line_counter = 0;
    
    //Reads file, adding each word to a 2d array
    while (fgets(lines[line_counter], 12, file) != NULL) {
        
        //Removes newline character from each word
        lines[line_counter][strlen(lines[line_counter]) - 1] = '\0';

        //printf("%s", lines[line_counter]);

        line_counter++;

        if (line_counter >= 500) {
            break;
        }
    }
    
    //prints random word from array
    srand(time(NULL));
   
    //Adds random words into result array
    for (int i = 0; i < NUM_WORDS; i++) {
        int random = rand() % 500;
        int line_length = strlen(lines[random]);
        strcpy(&result[result_index], lines[random]);
        result_index += line_length; 

        //Add spaces inbetween words
        result[result_index] = ' ';
        result_index++;
    }
    
    result[result_index] = '\0'; //Adds null character to end of string
    
    int result_length = sizeof(result) / sizeof(result[0]); //finds length of array for later use
    
    printw("\nPress ESC to exit\n");
    
    cursor_index = -1; //Sets to 0 so it can check if first char typed

    LOOP:while(1) {
        input = getch(); //Waits for user input
        
        if (cursor_index == -1) { //handles edge case where first char causes pointer to go out of index
            cursor_index++;
            goto LOOP;
        }
        if (input == 27) { //If escape key is pressed, exit program
            break;
        }

        //If input is correct, make character bold
        if (input == result[cursor_index]) {
   
            clear();
            refresh();

            attron(A_BOLD);
            for (int i = 0; i < cursor_index; i++) { //Prints correct text bold 
                printw("%c", result[i]);
            }
            attroff(A_BOLD);

            for (int i = cursor_index; i < (result_length - 1); i++) {
                printw("%c", result[i]);
             }


            cursor_index++;
        }

        //else do nothing
        else {
            continue;
        }
    }

        

    endwin();              
    //closes out of file
    fclose(file);

    return 0;
}

