#include "Tree.h"

Node_t* TreeNodeCtor(Tree_t data)
{
    Node_t* node = (Node_t*) calloc(1, sizeof(Node_t));
    if(node == NULL) return NULL;

    node->root = NULL;
    node->data = data;
    node->left = node->right = NULL;
    node->rank = 0;

    return node;
}


TreeErr_t TreeInsertLeft(Node_t* base_node, Node_t* inserting_node)
{
    if (base_node->left != NULL) return TREE_ERR_NODE_NOT_EMPTY;

    base_node->left = inserting_node;
    inserting_node->root = &base_node->left;
    inserting_node->rank = base_node->rank + 1;

    return TREE_OK;
}


TreeErr_t TreeInsertRight(Node_t* base_node, Node_t* inserting_node)
{
    if (base_node->right != NULL) return TREE_ERR_NODE_NOT_EMPTY;

    base_node->right = inserting_node;
    inserting_node->root = &base_node->right;
    inserting_node->rank = base_node->rank + 1;

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
    node->rank = 0;
    if (node->root) *node->root = NULL;

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


TreeErr_t PrintLeftTree(const Node_t* node, const char* mode)
{
    assert(node != NULL);
    assert(mode != NULL);
    assert(*mode == 'l' || *mode == 'r' || *mode == 'm');

    if (node->left)
    {
        return PrintTreeNode(node->left, mode);
    }

    return TREE_OK;
}


TreeErr_t PrintRightTree(const Node_t* node, const char* mode)
{
    assert(node != NULL);
    assert(mode != NULL);
    assert(*mode == 'l' || *mode == 'r' || *mode == 'm');

    if (node->right)
    {
        return PrintTreeNode(node->right, mode);
    }

    return TREE_OK;
}


TreeErr_t PrintTreeData(const Node_t* node, const char* mode)
{
    assert(node != NULL);
    assert(mode != NULL);
    assert(*mode == 'l' || *mode == 'r' || *mode == 'm');

    (void) mode;

    printf("%d", node->data);

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


FILE* StartHTMLfile(void)
{
    FILE* dump_file = fopen("dump.html", "w");
    if(dump_file == NULL) return NULL;

    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);

    fprintf(dump_file, "<!DOCTYPE html>\n"
                       "<html>\n"
                       "<head>\n"
                       "    <title>Tree Dump</title>\n"
                       "</head>\n"
                       "<body>\n"
                       "<style>\n"
                       "    * {\n"
                       "       font-size: 20px;\n"
                       "    }\n"
                       "</style>\n"
                       "<pre> Creation time (hours:min): %02d:%02d\n"
                            " data (day:month:year): %02d:%02d:%d </pre>",
                        time_info->tm_hour, time_info->tm_min,
                        time_info->tm_mday, time_info->tm_mon + 1,
                        time_info->tm_year + 1900);
    fclose(dump_file);
    return  dump_file;
}


TreeErr_t CreateDotFile(const Node_t* node)
{
    assert(node != NULL);

    FILE* dump_file = fopen("svg_dot/dump.dot", "w");
    assert(dump_file != NULL);

    fprintf(dump_file, "digraph DUMP\n"
                       "{\n"
                       "    rankdir=TB;\n"
                       "    splines=false;\n"
                       "    node["
                                // "shape=hexagon,"
                                // "style=\"filled\","
                                // "fillcolor=\"red\","
                                // "fontcolor=\"white\","
                                "fontname=\"Arial\","
                                "fontsize=24,"
                                // "width=1.8,"
                                // "height=1.8"
                                "];\n"
                       "    edge [style=\"bold\", "
                                 "arrowhead=\"normal\", "
                                 "splines=line, "
                                 "dir=normal]\n");

    int node_count = 0;
    MakeNodes(node, &node_count, dump_file);

    node_count = 0;
    MakeArrows(node, &node_count, dump_file);

    fprintf(dump_file,"}\n");

    fclose(dump_file);
    return TREE_OK;
}


void MakeNodes(const Node_t* node, int* node_count, FILE* file)
{
    assert(node != NULL);
    assert(file != NULL);

    fprintf(file,
        "    node%d [shape=plaintext, label=<\n"
        "        <TABLE BORDER=\"0\" "         // толщина внешней рамки таблицы
                 "CELLBORDER=\"2\" "           // толщина рамок ячеек
                 "CELLSPACING=\"3\" "          // расстояние между ячейками
                 "CELLPADDING=\"3\" "          // отступы внутри ячеек (от текста до рамки)
                 "BGCOLOR=\"#0bdfeeff\" "    // Цвет фона всей таблицы
                 "FIXEDSIZE=\"FALSE\" "        // фиксированный размер (игнорирует содержимое)
                 "ALIGN=\"CENTER\" "           // Горизонтальное выравнивание
                 "VALIGN=\"MIDDLE\" "          // Вертикальное выравнивание
                 "SIDES=\"LRTB\" "          // Какие стороны рамки показывать
                 ">\n"
        "            <TR><TD PORT=\"h\" "
                        "BGCOLOR=\"#777777ff\" "
                        "COLSPAN=\"2\" "
                        "COLOR=\"#383838ff\">"
                            "node%d"
                    "</TD></TR>\n"
        "            <TR><TD PORT=\"p\" "
                        "BGCOLOR=\"#db9721ff\" "
                        "COLSPAN=\"2\" "
                        "COLOR=\"#000000\">"
                            "%p"
                    "</TD></TR>\n"
        "            <TR><TD PORT=\"d\" "
                        "BGCOLOR=\"#540e96ff\" "
                        "COLSPAN=\"2\" "
                        "COLOR=\"#000000\">"
                            "%d"
                    "</TD></TR>\n",
        *node_count, *node_count, node, node->data
    );

    fprintf(file, "            <TR><TD PORT=\"l\" "
                                  "BGCOLOR=\"#db9721ff\" "
                                  "COLSPAN=\"1\" "
                                  "ALIGN=\"CENTER\" "
                                  "COLOR=\"#000000\">");
    if (node->left)
        fprintf(file, "%p</TD>", node->left);
    else
        fprintf(file, "0x000000000000</TD>");

    fprintf(file, "<TD PORT=\"r\" "
                  "BGCOLOR=\"#db9721ff\" "
                  "COLSPAN=\"1\" "
                  "ALIGN=\"CENTER\" "
                  "COLOR=\"#000000\">");
    if (node->right)
        fprintf(file, "%p</TD></TR>\n", node->right);
    else
        fprintf(file, "0x000000000000</TD></TR>\n");

    fprintf(file,
        "        </TABLE>\n"
        "    >];\n"
    );

    if (node->left)
    {
        ++*node_count;
        MakeNodes(node->left, node_count, file);
    }
    if (node->right)
    {
        ++*node_count;
        MakeNodes(node->right, node_count, file);
    }

    return;
}


void MakeArrows(const Node_t* node, int* node_count, FILE* file)
{
    assert(node != NULL);
    assert(file != NULL);

    int cur_node_count = *node_count;

    if (node->left)
    {
        fprintf(file, "    node%d:<l> -> node%d:n [dir=normal, color=\"#4d00a6ff\"];\n",
                       cur_node_count, ++*node_count);
        MakeArrows(node->left, node_count, file);
    }
    if (node->right)
    {
        fprintf(file, "    node%d:<r> -> node%d:n [dir=normal, color=\"#4d00a6ff\"];\n",
                      cur_node_count, ++*node_count);
        MakeArrows(node->right, node_count, file);
    }
}


TreeErr_t WriteInHtmlFile(const Node_t* node, int count_img, const char* func, const char* file, int line)
{
    assert(node != NULL);
    assert(func != NULL);
    assert(file != NULL);

    FILE* dump_file = fopen("dump.html", "a");
    CHECK_PTR(dump_file, FILE);

    fprintf(dump_file, "<pre><b>TreeDump from %s at %s:%d\n",
                       func, file, line);

    fprintf(dump_file, "    <img src=\"svg_dot/%ddump.svg\">\n",
                             count_img);

    fclose(dump_file);

    return TREE_OK;
}


int EndHTMLfile(void)
{
    FILE* dump_file = fopen("dump.html", "a");

    fprintf(dump_file, "</body>\n"
                       "</html>\n");

    return fclose(dump_file);
}
