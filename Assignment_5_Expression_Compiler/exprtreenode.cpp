#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    type = "";
    id = "";
    num = NULL;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    type = t;
    id = "";
    num = v;
}

ExprTreeNode::~ExprTreeNode()
{
    delete left;
    delete right;
}
