#include "Tree.h"

int main()
{
    Node_t* node2 = TreeNodeCtor(7, NULL, NULL);
    Node_t* node3 = TreeNodeCtor(20, NULL, NULL);
    Node_t* node1 = TreeNodeCtor(10, node2, node3);

    PrintTreeNode(node1, "m");
    printf("\n\n");

    Node_t* node4 = TreeNodeCtor(3, NULL, NULL);
    TreeSortInsert(node1, node4);

    PrintTreeNode(node1, "m");
    printf("\n\n");

    printf("|     root: %p (root value: %p)\n"
           "|         node2 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n\n",
           node2->root, *(node2->root), node2, node2->data, node2->left, node2->right);

    printf("|     root: %p (root value: %p)\n"
           "|         node4 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n\n",
           node4->root, *(node4->root), node4, node4->data, node4->left, node4->right);


    printf("\n");

    *(node4->root) = NULL;
    node4->data = 0;

    printf("ПОСЛЕ УДАЛЕНИЯ:\n");

    printf("|     root: %p (root value: %p)\n"
           "|         node2 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n\n",
           node2->root, *(node2->root), node2, node2->data, node2->left, node2->right);

    printf("|     root: %p (root value: %p)\n"
           "|         node4 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n\n",
           node4->root, *(node4->root), node4, node4->data, node4->left, node4->right);


    DeleteTreeNode(node4);
    free(node4);

    node4 = TreeNodeCtor(3, NULL, NULL);
    TreeInsertLeft(node2, node4);

    Node_t* node5 = TreeNodeCtor(35, NULL, NULL);
    TreeInsertRight(node3, node5);

    Node_t* node6 = TreeNodeCtor(15, NULL, NULL);
    TreeSortInsert(node1, node6);

    Node_t* node7 = TreeNodeCtor(1, NULL, NULL);
    TreeSortInsert(node1, node7);

    Node_t* node8 = TreeNodeCtor(9, NULL, NULL);
    TreeSortInsert(node1, node8);

    PrintTreeNode(node1, "m");
    printf("\n\n");

    TreeDump(node1, 1);
    system("google-chrome dump.html");


    DeleteTreeNode(node1);
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    free(node6);
    free(node7);
    free(node8);

    return 0;
}
