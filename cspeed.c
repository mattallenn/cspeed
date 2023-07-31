#include <stdio.h>
#include <stdlib.h>

#define STR 12 
#define LINES 250

int main() 
{
  
    FILE* file = fopen("1-1000.txt", "r");
    if (file == NULL) {
    
        printf("Error opening file\n");
        exit(1);
    }

    // Creates 2d array, num_lines is a row, maxchar is the array or chars to make a string
    char lines[LINE][STR];
    int line_counter = 0;

    while (fgets(lines[LINE], CHARS, file) != NULL) {
        
        //Removes the newline character

        printf("%s", line);
    }

}

