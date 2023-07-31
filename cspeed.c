#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#define NUM_WORDS 25

int main() 
{
    char text[NUM_WORDS * 12]; //Array of all characters of selected words

    initscr(); //Starts Curses
    raw(); //Disables line buffering
    noecho(); //Disables echoing of characters

    
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
    
    attron(A_BOLD); //Makes text bold
    for (int i = 0; i < NUM_WORDS; i++) {
        int random = rand() % 500;
        printw("%s ", lines[random]);
    }
    attroff(A_BOLD); //Turns off bold
    
    refresh();     
    getch(); //Waits for user input
    endwin();              
    //closes out of file
    fclose(file);

    return 0;
}

