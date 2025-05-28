#ifndef DATA_H
#define DATA_H

#define MAX_ID_LEN 64
#define MAX_DESC_LEN 256
#define MAX_PARENTS 10
#define MAX_CHILDREN 10

typedef struct {
    char id[MAX_ID_LEN];
    char description[MAX_DESC_LEN];
    char parents[MAX_PARENTS][MAX_ID_LEN];
    int parent_count;
    char children[MAX_CHILDREN][MAX_ID_LEN];
    int child_count;
} Requirement;

Requirement makenode(const Requirement* src);
int add_requirement(Requirement* arr, int count, int max, const Requirement* req);
void print_requirement(const Requirement* req);


//char* makenode();
//void makeconnection();

#endif
