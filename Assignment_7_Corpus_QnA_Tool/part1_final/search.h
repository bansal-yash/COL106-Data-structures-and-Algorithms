#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine
{
private:

public:
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);
};