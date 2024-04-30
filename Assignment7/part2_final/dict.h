#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class SymNode
{
public:
    string key;
    int height;
    int count = 0;
    SymNode *par;
    SymNode *left;
    SymNode *right;
    SymNode(string k);
    SymNode *LeftLeftRotation();
    SymNode *RightRightRotation();
    SymNode *LeftRightRotation();
    SymNode *RightLeftRotation();
    ~SymNode();
};

class SymbolTable
{
public:
    SymNode *root;
    SymbolTable();
    ~SymbolTable();
    void insert(string k);
    int get_count(string k);
};

class Dict
{
public:
    int m;
    SymbolTable **hash_table;

    Dict(int m1);

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);
};