#include "symtable.h"
using namespace std;

int check_balance(SymNode *temp)
{
    // 1 for right unbalanced
    // -1 for left unbalanced
    // 0 for balanced
    if (temp->left == NULL && temp->right == NULL)
    {
        return 0;
    }
    else if (temp->left == NULL && temp->right != NULL)
    {
        if (temp->right->height >= 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (temp->left != NULL && temp->right == NULL)
    {
        if (temp->left->height >= 1)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (temp->left->height - temp->right->height >= 2)
        {
            return -1;
        }
        else if (temp->left->height - temp->right->height <= -2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int get_height_1(SymNode *temp)
{
    if (temp->left == NULL && temp->right == NULL)
    {
        return 0;
    }
    else if (temp->left == NULL && temp->right != NULL)
    {
        return 1 + temp->right->height;
    }
    else if (temp->left != NULL && temp->right == NULL)
    {
        return 1 + temp->left->height;
    }
    else
    {
        return 1 + max(temp->left->height, temp->right->height);
    }
}

int check_heavy(SymNode *temp)
{
    // 1 for right heavy
    // -1 for left heavy
    // 0 for same
    if (temp->left == NULL && temp->right == NULL)
    {
        return 0;
    }
    else if (temp->left == NULL && temp->right != NULL)
    {
        return 1;
    }
    else if (temp->left != NULL && temp->right == NULL)
    {
        return -1;
    }
    else
    {
        if (temp->left->height - temp->right->height >= 1)
        {
            return -1;
        }
        else if (temp->left->height - temp->right->height <= -1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

SymbolTable::SymbolTable()
{
    size = 0;
}

void SymbolTable::insert(string k)
{
    size++;
    if (root == NULL)
    {
        root = new SymNode(k);
    }
    else
    {
        SymNode *temp = root;
        while (temp != NULL)
        {
            if (k.compare(temp->key) < 0)
            {
                if (temp->left == NULL)
                {
                    temp->left = new SymNode(k);
                    temp->left->par = temp;
                    break;
                }
                temp = temp->left;
            }
            else if (k.compare(temp->key) > 0)
            {
                if (temp->right == nullptr)
                {
                    temp->right = new SymNode(k);
                    temp->right->par = temp;
                    break;
                }
                temp = temp->right;
            }
        }

        temp->height = get_height_1(temp);
        while (temp->par != NULL)
        {
            temp = temp->par;
            temp->height = get_height_1(temp);
            if (check_balance(temp) == 0)
            {
                continue;
            }
            else if (check_balance(temp) == 1)
            {
                if (check_heavy(temp->right) == -1)
                {
                    if (temp->par == NULL)
                    {
                        root = temp->LeftRightRotation();
                    }
                    else
                    {
                        SymNode *ans = temp->LeftRightRotation();
                        if (ans->par->left == temp)
                        {
                            ans->par->left = ans;
                        }
                        else
                        {
                            ans->par->right = ans;
                        }
                        temp = ans;
                    }
                }
                else
                {
                    if (temp->par == NULL)
                    {
                        root = temp->LeftLeftRotation();
                    }
                    else
                    {
                        SymNode *ans = temp->LeftLeftRotation();
                        if (ans->par->left == temp)
                        {
                            ans->par->left = ans;
                        }
                        else
                        {
                            ans->par->right = ans;
                        }
                        temp = ans;
                    }
                }
            }
            else if (check_balance(temp) == -1)
            {
                if (check_heavy(temp->left) == 1)
                {
                    if (temp->par == NULL)
                    {
                        root = temp->RightLeftRotation();
                    }
                    else
                    {
                        SymNode *ans = temp->RightLeftRotation();
                        if (ans->par->left == temp)
                        {
                            ans->par->left = ans;
                        }
                        else
                        {
                            ans->par->right = ans;
                        }
                        temp = ans;
                    }
                }
                else
                {
                    if (temp->par == NULL)
                    {
                        root = temp->RightRightRotation();
                    }
                    else
                    {
                        SymNode *ans = temp->RightRightRotation();
                        if (ans->par->left == temp)
                        {
                            ans->par->left = ans;
                        }
                        else
                        {
                            ans->par->right = ans;
                        }
                        temp = ans;
                    }
                }
            }
        }
    }
}

void SymbolTable::remove(string k)
{
    if (root == NULL)
    {
        return;
    }
    SymNode *temp = root;
    while (temp != NULL)
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
            break;
        }
    }
    if (temp == NULL)
    {
        return;
    }
    size--;

    SymNode *to_balance = temp;
    if (temp->left == NULL && temp->right == NULL)
    {
        if (temp->par == NULL)
        {
            root = NULL;
            delete temp;
            return;
        }
        if (temp->par->right == temp)
        {
            temp->par->right = NULL;
        }
        else
        {
            temp->par->left = NULL;
        }
        to_balance = temp->par;
        delete temp;
    }
    else if (temp->left == NULL && temp->right != NULL)
    {
        if (temp->par == NULL)
        {
            root = temp->right;
            temp->right = NULL;
            root->par = NULL;
            delete temp;
            return;
        }
        if (temp->par->right == temp)
        {
            temp->par->right = temp->right;
        }
        else
        {
            temp->par->left = temp->right;
        }
        temp->right->par = temp->par;
        to_balance = temp->par;
        temp->right = NULL;
        delete temp;
    }
    else if (temp->left != NULL && temp->right == NULL)
    {
        if (temp->par == NULL)
        {
            root = temp->left;
            temp->left = NULL;
            root->par = NULL;
            delete temp;
            return;
        }
        if (temp->par->right == temp)
        {
            temp->par->right = temp->left;
        }
        else
        {
            temp->par->left = temp->left;
        }
        temp->left->par = temp->par;
        to_balance = temp->par;
        temp->left = NULL;
        delete temp;
    }
    else
    {
        SymNode *success = temp->right;
        while (success->left != NULL)
        {
            success = success->left;
        }
        string x = success->key;
        success->key = temp->key;
        temp->key = x;
        int z = success->address;
        success->address = temp->address;
        temp->address = z;
        temp = success;
        if (temp->par->right == temp)
        {
            temp->par->right = temp->right;
        }
        else
        {
            temp->par->left = temp->right;
        }
        if (temp->right != NULL)
        {
            temp->right->par = temp->par;
            temp->right = NULL;
        }
        to_balance = temp->par;
        delete temp;
    }

    temp = to_balance;
    temp->height = get_height_1(temp);

    if (check_balance(temp) == 1)
    {
        if (check_heavy(temp->right) == -1)
        {
            if (temp->par == NULL)
            {
                root = temp->LeftRightRotation();
            }
            else
            {
                SymNode *ans = temp->LeftRightRotation();
                if (ans->par->left == temp)
                {
                    ans->par->left = ans;
                }
                else
                {
                    ans->par->right = ans;
                }
                temp = ans;
            }
        }
        else
        {
            if (temp->par == NULL)
            {
                root = temp->LeftLeftRotation();
            }
            else
            {
                SymNode *ans = temp->LeftLeftRotation();
                if (ans->par->left == temp)
                {
                    ans->par->left = ans;
                }
                else
                {
                    ans->par->right = ans;
                }
                temp = ans;
            }
        }
    }
    else if (check_balance(temp) == -1)
    {
        if (check_heavy(temp->left) == 1)
        {
            if (temp->par == NULL)
            {
                root = temp->RightLeftRotation();
            }
            else
            {
                SymNode *ans = temp->RightLeftRotation();
                if (ans->par->left == temp)
                {
                    ans->par->left = ans;
                }
                else
                {
                    ans->par->right = ans;
                }
                temp = ans;
            }
        }
        else
        {
            if (temp->par == NULL)
            {
                root = temp->RightRightRotation();
            }
            else
            {
                SymNode *ans = temp->RightRightRotation();
                if (ans->par->left == temp)
                {
                    ans->par->left = ans;
                }
                else
                {
                    ans->par->right = ans;
                }
                temp = ans;
            }
        }
    }

    while (temp->par != NULL)
    {
        temp = temp->par;
        temp->height = get_height_1(temp);
        if (check_balance(temp) == 0)
        {
            continue;
        }
        else if (check_balance(temp) == 1)
        {
            if (check_heavy(temp->right) == -1)
            {
                if (temp->par == NULL)
                {
                    root = temp->LeftRightRotation();
                }
                else
                {
                    SymNode *ans = temp->LeftRightRotation();
                    if (ans->par->left == temp)
                    {
                        ans->par->left = ans;
                    }
                    else
                    {
                        ans->par->right = ans;
                    }
                    temp = ans;
                }
            }
            else
            {
                if (temp->par == NULL)
                {
                    root = temp->LeftLeftRotation();
                }
                else
                {
                    SymNode *ans = temp->LeftLeftRotation();
                    if (ans->par->left == temp)
                    {
                        ans->par->left = ans;
                    }
                    else
                    {
                        ans->par->right = ans;
                    }
                    temp = ans;
                }
            }
        }
        else if (check_balance(temp) == -1)
        {
            if (check_heavy(temp->left) == 1)
            {
                if (temp->par == NULL)
                {
                    root = temp->RightLeftRotation();
                }
                else
                {
                    SymNode *ans = temp->RightLeftRotation();
                    if (ans->par->left == temp)
                    {
                        ans->par->left = ans;
                    }
                    else
                    {
                        ans->par->right = ans;
                    }
                    temp = ans;
                }
            }
            else
            {
                if (temp->par == NULL)
                {
                    root = temp->RightRightRotation();
                }
                else
                {
                    SymNode *ans = temp->RightRightRotation();
                    if (ans->par->left == temp)
                    {
                        ans->par->left = ans;
                    }
                    else
                    {
                        ans->par->right = ans;
                    }
                    temp = ans;
                }
            }
        }
    }
}

int SymbolTable::search(string k)
{
    SymNode *temp = root;
    while (temp != NULL)
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
            return temp->address;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *temp = root;
    while (temp != NULL)
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
            temp->address = idx;
            return;
        }
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    delete root;
}