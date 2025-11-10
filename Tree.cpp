#include "Tree.h"

Node_t* TreeNodeCtor(Tree_t data, Node_t* left_som, Node_t* right_som)
{
    Node_t* node = (Node_t*) calloc(1, sizeof(Node_t));
    if(node == NULL) return NULL;

    node->root = NULL;
    node->data = data;
    node->left = left_som;
    node->right = right_som;

    if (left_som)  left_som->root  = &node->left;
    if (right_som) right_som->root = &node->right;

    return node;
}


TreeErr_t TreeInsertLeft(Node_t* base_node, Node_t* inserting_node)
{
    if (base_node->left != NULL) return TREE_ERR_NODE_NOT_EMPTY;

    base_node->left = inserting_node;
    inserting_node->root = &base_node->left;

    return TREE_OK;
}


TreeErr_t TreeInsertRight(Node_t* base_node, Node_t* inserting_node)
{
    if (base_node->right != NULL) return TREE_ERR_NODE_NOT_EMPTY;

    base_node->right = inserting_node;
    inserting_node->root = &base_node->right;

    return TREE_OK;
}


TreeErr_t TreeSortInsert(Node_t* root, Node_t* node)
{
    assert(root != NULL);
    assert(node != NULL);

    while(1)
    {
        if(node->data <= root->data)
        {
            if (root->left == node) return TREE_ERR_DUPLICATE_NODE;
            if (TreeInsertLeft(root, node) == TREE_OK) break;
            else root = root->left;
        }
        else
        {
            if (root->right == node) return TREE_ERR_DUPLICATE_NODE;
            if(TreeInsertRight(root, node) == TREE_OK) break;
            else root = root->right;
        }
    }

    return TREE_OK;
}


TreeErr_t DeleteTreeNode(Node_t* node)
{
    assert(node != NULL);

    if (node->left)  DeleteTreeNode(node->left);
    if (node->right) DeleteTreeNode(node->right);

    node->data = 0;
    if (node->root) *node->root = NULL;

    free(node);
    node = NULL;

    return TREE_OK;
}


TreeErr_t PrintTreeNode(const Node_t* node, const char* mode)
{
    typedef enum {
        PREORDER = 'l' - 'l',
        INORDER = 'm' - 'l',
        POSTORDER = 'r' - 'l'
    } TraverseMode_t;

    assert(node != NULL);
    assert(mode != NULL);
    assert(*mode == 'l' || *mode == 'r' || *mode == 'm');

    typedef TreeErr_t (* PrintFunc_t)(const Node_t* node, const char* mode);

    typedef struct
    {
        const char* mode;
        PrintFunc_t func1;
        PrintFunc_t func2;
        PrintFunc_t func3;
    } mode_s;

    mode_s modes[('r' - 'l') + 1] = {};

    modes[PREORDER] = {"l", PrintTreeData, PrintLeftTree,  PrintRightTree};
    modes[INORDER] = {"m", PrintLeftTree, PrintTreeData,  PrintRightTree};
    modes[POSTORDER] = {"r", PrintLeftTree, PrintRightTree, PrintTreeData};

    const mode_s* cur_mode = &modes[*mode - 'l'];

    printf("(");
    cur_mode->func1(node, cur_mode->mode);
    cur_mode->func2(node, cur_mode->mode);
    cur_mode->func3(node, cur_mode->mode);
    printf(")");

    return TREE_OK;
}


TreeErr_t TreeDump_(const Node_t* node, int count_img, const char* func, const char* file, int line)
{
    assert(node != NULL);

    CreateDotFile(node);
    char command[MAX_FILE_NAME];
    sprintf(command, "dot -Tsvg svg_dot/dump.dot -o svg_dot/%ddump.svg", count_img);
    system(command);

    if (StartHTMLfile() == NULL) return NULL_FILE;
    WriteInHtmlFile(node, count_img, func, file, line);

    if (EndHTMLfile() != 0) return END_FILE_ERR;

    return TREE_OK;
}
