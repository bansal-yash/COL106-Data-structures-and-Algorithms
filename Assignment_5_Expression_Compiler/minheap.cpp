#include "minheap.h"

string to_bin(int i)
{
    if (i == 0)
    {
        return "0";
    }
    string ans = "";
    int x = i;
    while (x != 0)
    {
        ans = to_string(x & 1) + ans;
        x = x >> 1;
    }
    return ans;
}

MinHeap::MinHeap()
{
    size = 0;
}

void MinHeap::push_heap(int num)
{
    if (root == NULL)
    {
        root = new HeapNode(num);
        size++;
    }
    else
    {
        size++;
        string s = to_bin(size);
        HeapNode *temp = root;
        for (int i = 1; i < s.size() - 1; i++)
        {
            if (s[i] == '0')
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        if (s[s.size() - 1] == '0')
        {
            temp->left = new HeapNode(num);
            temp->left->par = temp;
            temp = temp->left;
        }
        else
        {
            temp->right = new HeapNode(num);
            temp->right->par = temp;
            temp = temp->right;
        }
        while (temp->par != NULL && temp->val < temp->par->val)
        {
            int x = temp->val;
            temp->val = temp->par->val;
            temp->par->val = x;
            temp = temp->par;
        }
    }
}

int MinHeap::get_min()
{
    return root->val;
}

void MinHeap::pop()
{
    if (size == 1)
    {
        delete root;
        root = NULL;
        size = 0;
    }
    else
    {
        string s = to_bin(size);
        HeapNode *temp = root;
        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == '0')
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        int x = root->val;
        root->val = temp->val;
        temp->val = x;
        if (temp->par->left == temp)
        {
            temp->par->left = NULL;
        }
        else
        {
            temp->par->right = NULL;
        }
        delete temp;
        size--;
        temp = root;
        while (true)
        {
            if (temp->left == NULL)
            {
                break;
            }
            else if (temp->right == NULL)
            {
                if (temp->val > temp->left->val)
                {
                    int y = temp->val;
                    temp->val = temp->left->val;
                    temp->left->val = y;
                    temp = temp->left;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if ((temp->val < temp->left->val) && (temp->val < temp->right->val))
                {
                    break;
                }
                else if ((temp->val < temp->left->val) && (temp->val > temp->right->val))
                {
                    int a = temp->val;
                    temp->val = temp->right->val;
                    temp->right->val = a;
                    temp = temp->right;
                }
                else if ((temp->val > temp->left->val) && (temp->val < temp->right->val))
                {
                    int a = temp->val;
                    temp->val = temp->left->val;
                    temp->left->val = a;
                    temp = temp->left;
                }
                else
                {
                    if (temp->left->val > temp->right->val)
                    {
                        int a = temp->val;
                        temp->val = temp->right->val;
                        temp->right->val = a;
                        temp = temp->right;
                    }
                    else
                    {
                        int a = temp->val;
                        temp->val = temp->left->val;
                        temp->left->val = a;
                        temp = temp->left;
                    }
                }
            }
        }
    }
}

MinHeap::~MinHeap()
{
    delete root;
}