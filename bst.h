#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BstNode_ {
    int data;
    struct BstNode_ *left;
    struct BstNode_ *right;
} BstNode;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
