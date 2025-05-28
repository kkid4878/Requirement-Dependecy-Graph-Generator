#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "file-load-parse.h"

#define MAX_LINE 512


// Helper to trim whitespace
void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;
}

// Helper to split comma-separated values
int split_csv(const char *src, char arr[][MAX_ID_LEN], int max) {
    int count = 0;
    char buf[MAX_LINE];
    strncpy(buf, src, MAX_LINE-1);
    buf[MAX_LINE-1] = 0;
    char *token = strtok(buf, ",");
    while (token && count < max) {
        trim(token);
        if (strlen(token) > 0 && strcmp(token, "--") != 0)
            strncpy(arr[count++], token, MAX_ID_LEN-1);
        token = strtok(NULL, ",");
    }
    return count;
}

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

int parse_file(FILE *file, Requirement *reqs, int max_reqs)
{
    //reads loaded file
    //sends relevant data to database
    //every time it hits relevant data, calls make node from data
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
            char *p;
            if ((p = strstr(line, "ID:")) == line) {
                sscanf(line, "ID: %s", current.id);
            } else if ((p = strstr(line, "Description:")) == line) {
                char *desc = line + strlen("Description:");
                trim(desc);
                strncpy(current.description, desc, MAX_DESC_LEN-1);
            } else if ((p = strstr(line, "Parents:")) == line) {
                char *parents = line + strlen("Parents:");
                trim(parents);
                current.parent_count = split_csv(parents, current.parents, MAX_PARENTS);
            } else if ((p = strstr(line, "Children:")) == line) {
                char *children = line + strlen("Children:");
                trim(children);
                current.child_count = split_csv(children, current.children, MAX_CHILDREN);
            }
        }
    }
    return req_count;
};
/*
void print_dependency_report(const Requirement *reqs, int count) {
    for (int i = 0; i < count; ++i) {
        // Print the requirement itself
        printf("%s --\n", reqs[i].id);

        // Print parent relationships (parent -> this)
        for (int j = 0; j < reqs[i].parent_count; ++j) {
            if (strcmp(reqs[i].parents[j], "--") != 0 && strlen(reqs[i].parents[j]) > 0) {
                printf("%s -> %s\n", reqs[i].parents[j], reqs[i].id);
            }
        }

        // Print child relationships (this -> child)
        for (int j = 0; j < reqs[i].child_count; ++j) {
            if (strcmp(reqs[i].children[j], "--") != 0 && strlen(reqs[i].children[j]) > 0) {
                printf("%s -> %s\n", reqs[i].id, reqs[i].children[j]);
            }
        }
    }
}
*/
void write_dependency_report_with_header(const char *input_filename, const Requirement *reqs, int count, const char *outfilename) {
    FILE *in = fopen(input_filename, "r");
    FILE *out = fopen(outfilename, "w");
    if (!in || !out) {
        printf("Could not open input or output file.\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    // Copy the first three lines from input to output
    char buffer[512];
    for (int i = 0; i < 3; ++i) {
        if (fgets(buffer, sizeof(buffer), in)) {
            fputs(buffer, out);
        }
    }
    fputs("\n", out);

    int line = 4; // Start line numbering after the header
    for (int i = 0; i < count; ++i) {
        fprintf(out, "Line %d: %s --\n", line++, reqs[i].id);

        for (int j = 0; j < reqs[i].parent_count; ++j) {
            if (strcmp(reqs[i].parents[j], "--") != 0 && strlen(reqs[i].parents[j]) > 0) {
                fprintf(out, "Line %d: %s -> %s\n", line++, reqs[i].parents[j], reqs[i].id);
            }
        }
        for (int j = 0; j < reqs[i].child_count; ++j) {
            if (strcmp(reqs[i].children[j], "--") != 0 && strlen(reqs[i].children[j]) > 0) {
                fprintf(out, "Line %d: %s -> %s\n", line++, reqs[i].id, reqs[i].children[j]);
            }
        }
    }

    fclose(in);
    fclose(out);
}