#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>

#define NUM_WORDS 25
#define TEXT_WIDTH 36
#define NANO_PER_SEC 1000000000

typedef struct {
    int column;
    int row;
} Cursor;

int arr_length(char arr[]) {
    int length = 0;
    while (arr[length] != '\0') {
        length++;
    }
    return length;
}

int main() 
{
    struct timespec start, end;
    /* int miss_counter = 0; */
    double elapsed_time;
    int input_counter = 0;
    bool startgame = false;
    int cursor_index = 0; //Keeps track of which character user is on
    char result[NUM_WORDS * 15]; //Array of all characters of selected words
    int result_index = 0;
    char input;

    initscr(); //Starts Curses
    cbreak(); //Disables line buffering
    noecho(); //Disables echoing of characters
    curs_set(0); //Disables cursor
                       
    //Gets size of terminal to center text
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int row = (max_y / 2);
    int col = (max_x / 2);
    
    //Displays homepage
    char message []= "Welcome to cspeed!";
    char message2 []= "Press any key to start";
    char message3 []= "Press ESC to exit";
    //Displays homepage
    mvprintw(row, (col - (arr_length(message)/2)), "%s", message); //Prints text to screen
    mvprintw(row + 1, (col - (arr_length(message2)/2)), "%s", message2); //Prints text to screen
    mvprintw(row + 2, (col - (arr_length(message3)/2)), "%s", message3); //Prints text to screen
    refresh(); //Refreshes screen to show text
               
    /* //Opens file */ 
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
    
    int result_length = arr_length(result); 

    Cursor cursor_arr[result_length]; //Array of cursor structs  

    input = getch();
    if (input != 27) { // If Escape key is not pressed, start the game
        clear();
        startgame = true;
        
    }

    if (startgame) {
        // Display the text on the screen
        int width = (max_x) / 2;
        int height = (max_y) / 2;
        int num_lines = 0;

        refresh();
        for (int i = 0; i < result_length; i++) {
            if ((i % (width - 10)) == 0) {
                num_lines++;
            }

            mvprintw((height + num_lines), (width - (result_length / 2)), "%c", result[i]);

            width++;

            cursor_arr[i].column = width - (result_length / 2);
            cursor_arr[i].row = height + num_lines;
        }

        // Makes first character flash
        refresh(); // Refreshes screen to show text
    }


    // Main game loop
    while (1) 
        {
        
       input = getch(); // Waits for user input
        
        if (input_counter == 0) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            input_counter++;
        }

        if (input == 27) { // If escape key is pressed, exit program
            exit(0);
        }

        if (startgame) {
            if (input == result[cursor_index + 1]) {
                // If input is correct, make the character bold
                attron(A_BOLD);
                mvchgat(cursor_arr[cursor_index].row, cursor_arr[cursor_index].column, 1, A_BOLD, 1, NULL);
                attroff(A_BOLD);

                cursor_index++;
            }
            /* else { */
            /*     /1* miss_counter++; *1/ */
            /* } */

        }
        if ((cursor_index + 1) >= result_length) {
            clear();
            clock_gettime(CLOCK_MONOTONIC, &end);
            elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double) NANO_PER_SEC; 
            
            mvprintw(row, (col - (17)), "You finished in %.2f seconds!", elapsed_time); //Prints text to screen
            int raw_wpm = round((result_length / 5) / ((elapsed_time) / 60)); 
            /* int net_wpm = round(((result_length / 5) - miss_counter) / ((elapsed_time) / 60)); */
            /* long adj_wpm = ((result_length / 5) - miss_counter) / (end_time / 60); */
            /* printw("You finished in %f seconds!", end_time); //Prints text to screen */
            mvprintw(row + 2, (col - (17)), "%d Raw WPM", raw_wpm); //Prints text to screen */
            /* mvprintw(row + 3, (col - (17)), "%d Net WPM", net_wpm); //Prints text to screen *1/ */
            refresh();
            break;
        }
    }
    
    getch();

    endwin(); // Closes the ncurses window
    fclose(file); // Closes the file
    return 0;
    }
    
