#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
  
    FILE* file = fopen("1-1000.txt", "r");
    if (file == NULL) {
    
        printf("Error opening file\n");
        exit(1);
    }

    // Creates 2d array, num_lines is a row, maxchar is the array or chars to make a string
    char lines[1000][12];
    int line_counter = 0;
    
    //Reads file, adding each word to a 2d array
    while (fgets(lines[line_counter], 12, file) != NULL) {
        
        //Removes newline character from each word
        lines[line_counter][strlen(lines[line_counter]) - 1] = '\0';

        //printf("%s", lines[line_counter]);

        line_counter++;

        if (line_counter >= 1000) {
            break;
        }
    }
    
    printf("%s\n", lines[999]);
    
    //closes out of file
    fclose(file);
}

