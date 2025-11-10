#ifndef TREE_BASE
#define TREE_BASE

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef int Tree_t;

typedef struct Node_t
{
    Node_t** root;
    Tree_t data;
    Node_t* left;
    Node_t* right;
} Node_t;

typedef enum
{
    TREE_OK                 = 1 << 0,
    CALLLOC_ERR             = 1 << 1,
    TREE_ERR_NODE_NOT_EMPTY = 1 << 2,
    NULL_FILE               = 1 << 3,
    END_FILE_ERR            = 1 << 4,
    TREE_ERR_DUPLICATE_NODE = 1 << 5
} TreeErr_t;

#ifdef DEBUG
    #define CHECK_PTR(param, name) if (param == NULL)        \
                                    {                        \
                                        return NULL_##name;  \
                                    }
#else
    #define CHECK_PTR(param, name)
#endif // DEBUG


#endif // TREE_BASE
