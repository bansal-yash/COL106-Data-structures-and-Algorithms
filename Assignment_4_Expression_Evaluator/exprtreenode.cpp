/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    type = "";
    val = nullptr;
    evaluated_value = nullptr;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v)
{
    UnlimitedInt *one = new UnlimitedInt(1);
    type = t;
    if (type == "VAL")
    {
        val = new UnlimitedRational(v, one);
        evaluated_value = nullptr;
    }
    else
    {
        evaluated_value = new UnlimitedRational(v, one);
        val = nullptr;
    }
    id = "";
    left = nullptr;
    right = nullptr;
    delete one;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v)
{
    type = t;
    if (type == "VAL")
    {
        val = new UnlimitedRational(v->get_p(), v->get_q());
        evaluated_value = nullptr;
    }
    else
    {
        evaluated_value = new UnlimitedRational(v->get_p(), v->get_q());
        val = nullptr;
    }
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode()
{
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}