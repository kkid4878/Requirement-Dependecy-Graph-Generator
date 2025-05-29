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

    write_dependency_report_with_header(filename, reqs, count, "report.md");

    printf("=== Requirements Dependency Report ===\n\n");
    //print_dependency_report(reqs, count);

    //write_dependency_report_with_header(filename, reqs, count, "report.md");

    //print_requirement(reqs);

    /*
    printf("Parsed %d requirements:\n", count);
    for (int i = 0; i < count; ++i) {
        printf("ID: %s\n", reqs[i].id);
        printf("Description: %s\n", reqs[i].description);
        printf("Parents: ");
        for (int j = 0; j < reqs[i].parent_count; ++j)
            printf("%s ", reqs[i].parents[j]);
        printf("\nChildren: ");
        for (int j = 0; j < reqs[i].child_count; ++j)
            printf("%s ", reqs[i].children[j]);
        printf("\n\n");
    }*/
    // You can now generate a report as needed
    return 0;
    

}
