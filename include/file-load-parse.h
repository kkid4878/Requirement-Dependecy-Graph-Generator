#ifndef FILE_LOAD_PARSE_H
#define FILE_LOAD_PARSE_H //apparently this is needed to avoid multiple definitions, idk why but it works
#include <stdio.h>

#include "data.h"
#include "regex.h" //parse w/ regex if time allows, but even getting it to download is cring

//void load_file();
//int parse_file();
void trim(char *str);
int split_csv(const char *src, char arr[][MAX_ID_LEN], int max);
//void load_file(char* filename);
int parse_file(FILE *file, Requirement *reqs, int max_reqs);
//void print_dependency_report(const Requirement *reqs, int count);
void write_dependency_report_with_header(const char *input_filename, const Requirement *reqs, int count, const char *outfilename);

//commented out func that don't work, keeping definitions bc didn't save the version with them anywhere
//thought i had github auto saving but no

#endif 
