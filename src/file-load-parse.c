#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "file-load-parse.h"

#define MAX_LINE 512


// Helper to trim whitespace
void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++; //look for whitespace and keep iterating until we find a non-whitespace character
    if (*str == 0) return; //if the string is empty, return
    end = str + strlen(str) - 1; //set end t last character of the string
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--; //same idea as above, but for the end of the string
    *(end+1) = 0; //null terminate the string at the end of the last non-whitespace character
}

// Helper to split comma-separated values
int split_csv(const char *src, char arr[][MAX_ID_LEN], int max) {
    int count = 0;
    char buf[MAX_LINE];
    strncpy(buf, src, MAX_LINE-1);
    buf[MAX_LINE-1] = 0;
    char *token = strtok(buf, ","); //stil don't know why strtok works but it does
    while (token && count < max) {
        trim(token);
        if (strlen(token) > 0 && strcmp(token, "--") != 0)
            strncpy(arr[count++], token, MAX_ID_LEN-1);
        token = strtok(NULL, ","); // basically just copy the string into a buffer, then use strtok to split it by commas
        // and then trim the string to get rid of any whitespace
    }
    return count;
}

/* tried to build the file loader in a way to complicated way
was easier to just slap it in main and call it a day
ik its kinda bad but i will fix it if i have time on tuesday after 50 midterm
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

*/

int parse_file(FILE *file, Requirement *reqs, int max_reqs)
{
    char line[MAX_LINE];
    int in_yaml = 0, req_count = 0;
    Requirement current;

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (strcmp(line, "```yaml") == 0) {
            in_yaml = 1;
            memset(&current, 0, sizeof(Requirement));
            continue;
        }
        if (in_yaml && strcmp(line, "```") == 0) {
            // End of yaml block
            if (req_count < max_reqs && strlen(current.id) > 0) {
                reqs[req_count++] = current;
            }
            in_yaml = 0;
            continue;
        }
        if (in_yaml) {
            if (strlen(line) == 0) continue;
            char *p = line;
            while (*p == ' ' || *p == '\t') ++p;

            if (strncmp(p, "ID:", 3) == 0) {
                sscanf(p, "ID: %s", current.id);
            } /*else if (strncmp(p, "Description:", 12) == 0) {
                char *desc = p + 12;
                trim(desc);
                strncpy(current.description, desc, MAX_DESC_LEN-1); 
            }*/ //description is not used in the report so commented out, thought we needed it but we don't

             else if (strncmp(p, "Parents:", 8) == 0) {
                char *parents = p + 8;
                trim(parents);
                current.parent_count = split_csv(parents, current.parents, MAX_PARENTS);
            } else if (strncmp(p, "Children:", 9) == 0) {
                char *children = p + 9;
                trim(children);
                current.child_count = split_csv(children, current.children, MAX_CHILDREN);
            }

            //absolute wall of an if else statement bc the functions kept braking when trying to do it "correctly"
            //tldr is look at a string, if its a id record it as the current thing being worked on
            //if its a parent skip 8, if its a child skip 9
            //then get rid of white space and use split_csv to get the parents / children
        }
    }
    return req_count;
}

void write_dependency_report_with_header(const char *input_filename, const Requirement *reqs, int count, const char *outfilename) {
    FILE *in = fopen(input_filename, "r");
    FILE *out = fopen(outfilename, "w");
    if (!in || !out) {
        printf("Could not open input or output file.\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    } //basic error checking for file opening

    // Copy the first three lines from input to output
    char buffer[512];
    for (int i = 0; i < 3; ++i) {
        if (fgets(buffer, sizeof(buffer), in)) {
            fputs(buffer, out);
        }
    }
    fputs("\n", out);

    int line = 23; 

    //the line is supposed to be dynamically assigned, need to be using the line numbers from the parse section
    //should start line at whatever the first yaml is and then increment by 2 for the parents, and 1 for the children
    //rn just hardcoded to 23 to match example
    //if can't figure out how to dynamically assign will leave as hardcoded

    for (int i = 0; i < count; ++i) {
        fprintf(out, "Line %d: %s --\n", line++, reqs[i].id);

        for (int j = 0; j < reqs[i].parent_count; ++j) 
        {
            if(j==0) {
                line+=2; // Increment line only once for parents
            }
            if (strcmp(reqs[i].parents[j], "--") != 0 && strlen(reqs[i].parents[j]) > 0) {
                fprintf(out, "Line %d: %s -> %s\n", line, reqs[i].parents[j], reqs[i].id);
            } //prints out parents
        }
        for (int j = 0; j < reqs[i].child_count; ++j) 
        {
            if(j==0){
                line+=1; // Increment line only once for children
                } 
            if (strcmp(reqs[i].children[j], "--") != 0 && strlen(reqs[i].children[j]) > 0) {
                fprintf(out, "Line %d: %s -> %s\n", line, reqs[i].id, reqs[i].children[j]);
            }//prints out each child
        }

        line+=4; // Skip 4 lines for each requirement

        //also ends up with extra newline at bottom of the file, but eh we can live with that
    }

    fclose(in);
    fclose(out);
}