// Do NOT add any other includes
#include "dict.h"

// Symnode started
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
SymNode::SymNode(string k)
{
    key = k;
    height = 0;
    count = 1;
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
    *file_to_be_dumped1 << this->key << ", " << this->count << endl;
    if (left != NULL)
    {
        left->file_to_be_dumped1 = file_to_be_dumped1;
        delete left;
    }
    if (right != NULL)
    {
        right->file_to_be_dumped1 = file_to_be_dumped1;
        delete right;
    }
}
// Symnode ended

// Symtable started
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
}
void SymbolTable::insert(string k)
{
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
            else
            {
                temp->count = temp->count + 1;
                return;
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
int SymbolTable::get_count(string k)
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
            return temp->count;
        }
    }
    return 0;
}
SymbolTable::~SymbolTable()
{
    if (root != NULL)
    {
        root->file_to_be_dumped1 = file_to_be_dumped;
        delete root;
    }
}
// Symtable ended

// hash function started
int hash1(string &s, int m)
{
    const int p = 31;
    const int mod = 1e9 + 9; // A large prime for avoiding overflow

    int h = 0;
    int power = 1;

    for (char c : s)
    {
        h = (1LL * h * p + (c - 'a' + 1)) % mod;
        power = (1LL * power * p) % mod;
    }

    return abs((h % mod) % m);
}

// hash function ended

Dict::Dict()
{
    m = 10007;
    hash_table = new SymbolTable *[m];
    for (int i = 0; i < m; i++)
    {
        hash_table[i] = new SymbolTable();
    }
}

Dict::~Dict()
{
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    string temp = "";
    int sz = sentence.size();
    for (int i = 0; i < sz + 1; i++)
    {
        int ascii = -1;
        if(i!=sz){
            ascii = static_cast<int>(sentence[i]);
        }
        if (i == sz || sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == ',' || sentence[i] == '-' ||
            sentence[i] == ':' || sentence[i] == '!' || sentence[i] == '"' || sentence[i] == '\'' || sentence[i] == '(' || sentence[i] == ')' ||
            sentence[i] == ';' || sentence[i] == '@'||  sentence[i] == '['|| sentence[i] == ']'||sentence[i] == '?')
        {
            if (temp != "")
            {   
                int h = hash1(temp, m);
                SymbolTable *curr = hash_table[h];
                curr->insert(temp);
                temp = "";
            }
            else{
                continue;
            }
        }
        else
        {
            if (ascii <= 90 && ascii >= 65)
            {
                char r = static_cast<char>(ascii + 32);
                temp = temp + r;
            }
            else
            {
                char r = static_cast<char>(ascii);
                temp = temp + r;
            }
        }

    }
}

int Dict::get_word_count(string word)
{
    int h = hash1(word, m);
    SymbolTable *curr = hash_table[h];
    return curr->get_count(word);
}

void Dict::dump_dictionary(string filename)
{
    std::ofstream outfile(filename, std::ios::app);
    std::ofstream &temp = outfile;
    for (int i = 0; i < m; i++)
    {
        hash_table[i]->file_to_be_dumped = &temp;
        delete hash_table[i];
    }
    outfile.close();
    return;
}

// int main()
// {
//     Dict *temp = new Dict();
//     ifstream file("input.txt");
//     // temp->insert_sentence(1, 1, 1, 1, "This is Sanya");
//     temp->insert_sentence(1, 1, 1, 1, "1. A CONFESSION 1");
//     temp->insert_sentence(1, 1, 1, 1, "[1884] I wrote it on a slip of paper and handed it to him myself.");
//     // temp->insert_sentence(1, 1, 1, 1, " In this note not only did I confess my guilt, but I asked adequate punishment for it, and closed with a request to him not to punish himself for my offence.");
//     temp->dump_dictionary("output.txt");
// }
