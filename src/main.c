#include <stdio.h>
#include <string.h>
#include "file-load-parse.h"
#include "data.h"

int main() {
        char filename[256];
    printf("Enter requirements file path: "); //tried to make file loader in file-load-parse.c, didnt work, see comments in that file
    fgets(filename, sizeof(filename), stdin); 
    filename[strcspn(filename, "\n")] = 0; // Remove newline?

    FILE *file = fopen(filename, "r");
    Requirement reqs[100]; //make struct array to hold stuff
    
    int count = parse_file(file, reqs, 100); //call parse file which is like 90% of the code
    fclose(file);

    write_dependency_report_with_header(filename, reqs, count, "rdgg-report-76716794.md"); //i think this name is right, idk if prof actually wants <> around student id but i dont think her does

    printf("=== Requirements Dependency Report ===\n\n"); //use to check that it ran without failing
    
    return 0;
    

}
