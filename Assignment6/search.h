// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class senten
{
public:
    int b_code = 0;
    int pg = 0;
    int para = 0;
    int sen_no = 0;
    vector<char> sen;

    senten(int book_code, int page, int paragraph, int sentence_no, string sentence);
};

class SearchEngine
{
private:
    vector<senten *> texts;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/
};