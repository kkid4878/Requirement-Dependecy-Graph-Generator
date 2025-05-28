#include <stdio.h>
#include <string.h>

void load_file(char* filename)
{
    char input[256];
    printf("Enter Makefile path (default: Makefile): ");
    fgets(input, sizeof(input), stdin);
    

     size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    if (input[0] == '\0') {
        strcpy(filename, "Makefile");
    } else {
        strcpy(filename, input);
    }

    FILE *file = fopen(filename, "r");
    if (file) {
        printf("File '%s' opened successfully.\n", filename);
        fclose(file);
    } else {
        printf("Could not open file: %s\n", filename);
    }
    //this function opens a file from the user input
    //and calls parse file
};

void parse_file()
{
    //reads loaded file
    //sends relevant data to database
    //every time it hits relevant data, calls make node from data
    
};