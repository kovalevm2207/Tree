#include "Tree.h"

int main()
{
    Node_t* node1 = TreeNodeCtor(10);
    Node_t* node2 = TreeNodeCtor(7);
    TreeSortInsert(node1, node2);

    Node_t* node3 = TreeNodeCtor(20);
    TreeSortInsert(node1, node3);

    PrintTreeNode(node1, "m");
    printf("\n\n");

    Node_t* node4 = TreeNodeCtor(3);
    TreeSortInsert(node1, node4);

    PrintTreeNode(node1, "m");
    printf("\n\n");

    printf("|     root: %p (root value: %p)\n"
           "|         node2 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n"
           "|    rank = %d\n\n", node2->root, *(node2->root), node2, node2->data, node2->left, node2->right, node2->rank);

    printf("|     root: %p (root value: %p)\n"
           "|         node4 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n"
           "|    rank = %d\n\n", node4->root, *(node4->root), node4, node4->data, node4->left, node4->right, node4->rank);


    printf("\n");

    *(node4->root) = NULL;
    node4->data = 0;

    printf("ПОСЛЕ УДАЛЕНИЯ:\n");

    printf("|     root: %p (root value: %p)\n"
           "|         node2 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n\n", node2->root, *(node2->root), node2, node2->data, node2->left, node2->right);

    printf("|     root: %p (root value: %p)\n"
           "|         node4 (addres in mem: %p)\n"
           "|      data: %3d\n"
           "|       left:      right:\n"
           "| %p             %p\n\n", node4->root, *(node4->root), node4, node4->data, node4->left, node4->right);


    DeleteTreeNode(node4);
    free(node4);

    node4 = TreeNodeCtor(3);
    TreeInsertLeft(node2, node4);

    Node_t* node5 = TreeNodeCtor(35);
    TreeInsertRight(node3, node5);

    Node_t* node6 = TreeNodeCtor(15);
    TreeSortInsert(node1, node6);

    Node_t* node7 = TreeNodeCtor(1);
    TreeSortInsert(node1, node6);

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

    return 0;
}
