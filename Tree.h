#ifndef TREE
#define TREE

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
    TREE_ERR_NODE_NOT_EMPTY = 1 << 2
} TreeErr_t;

Node_t* TreeNodeCtor(Tree_t data);
TreeErr_t TreeInsertLeft(Node_t* base_node, Node_t* inserting_node);
TreeErr_t TreeInsertRight(Node_t* base_node, Node_t* inserting_node);
TreeErr_t TreeSortInsert(Node_t* root, Node_t* node);
TreeErr_t DeleteTreeNode(Node_t* node);

TreeErr_t PrintTreeNode(const Node_t* node, const char* mode);
TreeErr_t PrintLeftTree(const Node_t* node, const char* mode);
TreeErr_t PrintRightTree(const Node_t* node, const char* mode);
TreeErr_t PrintTreeData(const Node_t* node, const char* mode);

#endif
