#include <stdio.h>
#include <string.h>
#include "file-load-parse.h"
#include "data.h"

int main() {
        char filename[256];
    printf("Enter requirements file path: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline

    FILE *file = fopen(filename, "r");
    Requirement reqs[100];
    
    
    int count = parse_file(file, reqs, 100);
    fclose(file);

    write_dependency_report_with_header(filename, reqs, count, "rdgg-report-76716794.md");

    printf("=== Requirements Dependency Report ===\n\n");
    
    return 0;
    

}
