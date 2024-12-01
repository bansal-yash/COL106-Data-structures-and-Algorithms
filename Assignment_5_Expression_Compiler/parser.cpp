#include "parser.h"
#include <iostream>

Parser::Parser()
{
    expr_trees.resize(0);
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression)
{
    vector<string> code;
    for ( int i = 0; i < expression.size() ; i++)
    {
        code.push_back(expression[i]);
    }
    
    ExprTreeNode *newtree = new ExprTreeNode();
    newtree->type = "EQUAL";
    newtree->left = new ExprTreeNode();
    if (code[0] == "del")
    {
        newtree->left->type = "DEL";
    }
    else if (code[0] == "ret")
    {
        newtree->left->type = "RET";
    }
    else
    {
        newtree->left->type = "VAR";
        newtree->left->id = code[0];
    }

    vector<ExprTreeNode *> parents;
    newtree->right = new ExprTreeNode();
    ExprTreeNode *current = newtree->right;

    if (code[2] != "(")
    {
        if (((static_cast<int>(code[2][0]) >= 48) && (static_cast<int>(code[2][0]) <= 57)) || code[2][0] == '-')
        {
            current->type = "VAL";
            current->num = stoi(code[2]);
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
                    current->num = stoi(code[i]);
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
    if (newtree->left->type == "VAR")
    {
        if (symtable->search(newtree->left->id) == -2)
        {
            symtable->insert(newtree->left->id);
        }
    }
    if (newtree->left->type == "DEL")
    {
        if (symtable->search(newtree->right->id) != -2)
        {
            last_deleted = symtable->search(newtree->right->id);
            symtable->remove(newtree->right->id);
        }
    }
    expr_trees.push_back(newtree);
}

Parser::~Parser()
{
    delete symtable;
    while (!expr_trees.empty())
    {
        delete expr_trees.back();
        expr_trees.pop_back();
    }
}