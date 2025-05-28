#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

// Example: create a new Requirement node (deep copy)
Requirement makenode(const Requirement* src) {
    Requirement node;
    memcpy(&node, src, sizeof(Requirement));
    return node;
}

// Example: add a Requirement to an array (returns new count)
int add_requirement(Requirement* arr, int count, int max, const Requirement* req) {
    if (count < max) {
        arr[count] = makenode(req);
        return count + 1;
    }
    return count;
}

// Example: print a Requirement (for debugging)
void print_requirement(const Requirement* req) {
    printf("ID: %s\n", req->id);
    printf("Description: %s\n", req->description);
    printf("Parents: ");
    for (int i = 0; i < req->parent_count; ++i)
        printf("%s ", req->parents[i]);
    printf("\nChildren: ");
    for (int i = 0; i < req->child_count; ++i)
        printf("%s ", req->children[i]);
    printf("\n");
}