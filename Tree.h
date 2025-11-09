#ifndef TREE
#define TREE

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

const int MAX_FILE_NAME = 100;

typedef int Tree_t;

typedef struct Node_t
{
    Node_t** root;
    Tree_t data;
    Node_t* left;
    Node_t* right;
    int rank;
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

Node_t* TreeNodeCtor(Tree_t data);
TreeErr_t TreeInsertLeft(Node_t* base_node, Node_t* inserting_node);
TreeErr_t TreeInsertRight(Node_t* base_node, Node_t* inserting_node);
TreeErr_t TreeSortInsert(Node_t* root, Node_t* node);
TreeErr_t DeleteTreeNode(Node_t* node);

TreeErr_t PrintTreeNode(const Node_t* node, const char* mode);
TreeErr_t PrintLeftTree(const Node_t* node, const char* mode);
TreeErr_t PrintRightTree(const Node_t* node, const char* mode);
TreeErr_t PrintTreeData(const Node_t* node, const char* mode);

TreeErr_t TreeDump_(const Node_t* node, int count_im, const char* func, const char* file, int line);
FILE* StartHTMLfile(void);

TreeErr_t CreateDotFile(const Node_t* node);
void MakeNodes(const Node_t* node, int* node_count, FILE* file);
void MakeArrows(const Node_t* node, int* node_count, FILE* file);
TreeErr_t WriteInHtmlFile(const Node_t* node, int count_img, const char* func, const char* file, int line);

int EndHTMLfile(void);

#define TreeDump(node, count_img) TreeDump_(node, count_img, __func__, __FILE__, __LINE__)
#define STRING(text) #text

#ifdef DEBUG
    #define CHECK_PTR(param, name) if (param == NULL)        \
                                    {                        \
                                        return NULL_##name;  \
                                    }
#else
    #define CHECK_PTR(param, name)
#endif // DEBUG

#endif // TREE
