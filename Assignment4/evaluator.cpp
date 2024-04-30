/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

UnlimitedRational *evaltree(ExprTreeNode *root, SymbolTable *symtable)
{
    if (root->type == "VAL")
    {
        return root->val;
    }
    else if (root->type == "VAR")
    {
        UnlimitedRational *x = symtable->search(root->id);
        root->val = new UnlimitedRational(x->get_p(), x->get_q());
        root->evaluated_value = new UnlimitedRational(x->get_p(), x->get_q());
        return root->val;
    }
    else
    {
        UnlimitedRational *a = evaltree(root->left, symtable);
        UnlimitedRational *b = evaltree(root->right, symtable);
        if (root->type == "ADD")
        {
            root->evaluated_value = UnlimitedRational::add(a, b);
        }
        else if (root->type == "SUB")
        {
            root->evaluated_value = UnlimitedRational::sub(a, b);
        }
        else if (root->type == "MUL")
        {
            root->evaluated_value = UnlimitedRational::mul(a, b);
        }
        else if (root->type == "DIV")
        {
            root->evaluated_value = UnlimitedRational::div(a, b);
        }
        return root->evaluated_value;
    }
}

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}

Evaluator::~Evaluator()
{
    delete symtable;
    while (!expr_trees.empty())
    {
        delete expr_trees.back();
        expr_trees.pop_back();
    }
}

void Evaluator::parse(vector<string> code)
{
    ExprTreeNode *newtree = new ExprTreeNode();
    newtree->type = "EQUAL";
    newtree->left = new ExprTreeNode();
    newtree->left->type = "VAR";
    newtree->left->id = code[0];

    vector<ExprTreeNode *> parents;
    newtree->right = new ExprTreeNode();
    ExprTreeNode *current = newtree->right;

    if (code[2] != "(")
    {
        if (((static_cast<int>(code[2][0]) >= 48) && (static_cast<int>(code[2][0]) <= 57)) || code[2][0] == '-')
        {
            current->type = "VAL";
            UnlimitedInt *one = new UnlimitedInt(1);
            UnlimitedInt *temp = new UnlimitedInt(stoi(code[2]));
            current->val = new UnlimitedRational(temp, one);
            delete temp;
            delete one;
        }
        else
        {
            current->type = "VAR";
            current->id = code[2];
        }
    }
    else
    {
        int s = code.size();
        for (int i = 2; i < s; i++)
        {
            if (code[i] == "(")
            {
                current->left = new ExprTreeNode();
                parents.push_back(current);
                current = current->left;
            }
            else if (code[i] == "+" || code[i] == "-" || code[i] == "*" || code[i] == "/")
            {
                if (code[i] == "+")
                {
                    current->type = "ADD";
                }
                else if (code[i] == "-")
                {
                    current->type = "SUB";
                }
                else if (code[i] == "*")
                {
                    current->type = "MUL";
                }
                else if (code[i] == "/")
                {
                    current->type = "DIV";
                }
                current->right = new ExprTreeNode();
                parents.push_back(current);
                current = current->right;
            }
            else if (code[i] == ")")
            {
                current = parents.back();
                parents.pop_back();
            }
            else
            {
                if (((static_cast<int>(code[i][0]) >= 48) && (static_cast<int>(code[i][0]) <= 57)) || code[i][0] == '-')
                {
                    current->type = "VAL";
                    UnlimitedInt *one = new UnlimitedInt(1);
                    UnlimitedInt *temp = new UnlimitedInt(stoi(code[i]));
                    current->val = new UnlimitedRational(temp, one);
                    delete temp;
                    delete one;
                }
                else
                {
                    current->type = "VAR";
                    current->id = code[i];
                }

                current = parents.back();
                parents.pop_back();
            }
        }
    }
    expr_trees.push_back(newtree);
}

void Evaluator::eval()
{
    ExprTreeNode *to_evaluate = expr_trees.back();
    UnlimitedRational *x = evaltree(to_evaluate->right, symtable);
    UnlimitedRational *temp = new UnlimitedRational(x->get_p(), x->get_q());
    to_evaluate->left->evaluated_value = temp;
    ExprTreeNode *var = to_evaluate->left;
    symtable->insert(var->id, var->evaluated_value);
}