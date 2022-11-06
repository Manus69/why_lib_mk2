#ifndef AVL_NODE_T_X_H
#define AVL_NODE_T_X_H

#include "template_interface.h"
#include "avl_node_T_X_interface.h"

struct AVLNode_T_X
{
    TYPE         key;
    XYPE         value;

    AVLNode_T_X* parent;
    AVLNode_T_X* left;
    AVLNode_T_X* right;
    int          balance;
};

#endif