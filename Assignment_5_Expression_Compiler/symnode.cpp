#include "symnode.h"

int get_height(SymNode *temp)
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

SymNode::SymNode()
{
    key = "";
    height = -1;
}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *ans = this->right;
    this->right = ans->left;
    ans->left = this;
    if (this->right != NULL)
    {
        this->right->par = this;
    }
    ans->par = this->par;
    this->par = ans;
    this->height = get_height(this);
    ans->height = get_height(ans);
    return ans;
}

SymNode *SymNode::RightRightRotation()
{
    SymNode *ans = this->left;
    this->left = ans->right;
    ans->right = this;
    if (this->left != NULL)
    {
        this->left->par = this;
    }
    ans->par = this->par;
    this->par = ans;
    this->height = get_height(this);
    ans->height = get_height(ans);
    return ans;
}

SymNode *SymNode::LeftRightRotation()
{
    this->right = this->right->RightRightRotation();
    this->height = get_height(this);
    SymNode *ans = this->LeftLeftRotation();
    return ans;
}

SymNode *SymNode::RightLeftRotation()
{
    this->left = this->left->LeftLeftRotation();
    this->height = get_height(this);
    SymNode *ans = this->RightRightRotation();
    return ans;
}

SymNode::~SymNode()
{
    delete left;
    delete right;
}