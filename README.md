# cspeed
A simple, lightweight, fast typing speed game written in C.

**1. Open File**
- Check for file errors 
	``` c
	if (file == NULL) {
		printf("Cannot open file\n");
		exit(1);
		}
	```

**2. Load file contents into an array**
- define the number of lines and max number of chars in each line  
- Initialize 2d array `char lines[LINE_NUM][STR]` where `LINE_NUM` is the line that the word is on (its index), and `CHARS` is the array of chars that make up that word. 
- use `fgets()` to load contents from file one line at a time eg. `fgets(string, max num of chars, file)`
- store str into its own index using a line counter eg.
	```c
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
	```
**Make sure to include <string.h>**
