/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
using namespace std;

SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
}

SymbolTable::~SymbolTable()
{
    delete root;
}

void SymbolTable::insert(string k, UnlimitedRational *v)
{
    if (root == nullptr)
    {
        root = new SymEntry(k, v);
        size++;
    }
    else
    {
        SymEntry *temp = root;
        while (temp != nullptr)
        {
            if (k.compare(temp->key) < 0)
            {
                if (temp->left == nullptr)
                {
                    temp->left = new SymEntry(k, v);
                    size++;
                    break;
                }
                temp = temp->left;
            }
            else if (k.compare(temp->key) > 0)
            {
                if (temp->right == nullptr)
                {
                    temp->right = new SymEntry(k, v);
                    size++;
                    break;
                }
                temp = temp->right;
            }
            else
            {
                return;
            }
        }
    }
}

void SymbolTable::remove(string k)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        SymEntry *parent = nullptr;
        SymEntry *temp = root;

        while (temp != nullptr)
        {
            if (k.compare(temp->key) < 0)
            {
                parent = temp;
                temp = temp->left;
            }
            else if (k.compare(temp->key) > 0)
            {
                parent = temp;
                temp = temp->right;
            }
            else
            {
                if (temp->left == nullptr)
                {
                    if (parent == nullptr)
                    {
                        root = temp->right;
                    }
                    else
                    {
                        if (parent->right == temp)
                        {
                            parent->right = temp->right;
                        }
                        else
                        {
                            parent->left = temp->right;
                        }
                    }
                }
                else if (temp->right == nullptr)
                {
                    if (parent == nullptr)
                    {
                        root = temp->left;
                    }
                    else
                    {
                        if (parent->right == temp)
                        {
                            parent->right = temp->left;
                        }
                        else
                        {
                            parent->left = temp->left;
                        }
                    }
                }
                else
                {
                    SymEntry *success = temp->right;
                    if (success->left == nullptr)
                    {
                        success->left = temp->left;
                        if (parent->left == temp)
                        {
                            parent->left = success;
                        }
                        else
                        {
                            parent->right = success;
                        }
                    }
                    else
                    {
                        SymEntry *successpar = success;
                        success = success->left;
                        while (success->left != nullptr)
                        {
                            successpar = successpar->left;
                            success = success->left;
                        }
                        successpar->left = success->right;
                        success->left = temp->left;
                        success->right = temp->right;
                        if (parent->left == temp)
                        {
                            parent->left = success;
                        }
                        else
                        {
                            parent->right = success;
                        }
                    }
                }

                temp->left = nullptr;
                temp->right = nullptr;
                delete temp;
                size--;
            }
        }
    }
}

UnlimitedRational *SymbolTable::search(string k)
{
    SymEntry *temp = root;
    while (temp != nullptr)
    {
        if (k.compare(temp->key) < 0)
        {
            temp = temp->left;
        }
        else if (k.compare(temp->key) > 0)
        {
            temp = temp->right;
        }
        else
        {
            return temp->val;
        }
    }
    return nullptr;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}