// Do NOT add any other includes
#include "search.h"

senten::senten(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    b_code = book_code;
    pg = page;
    para = paragraph;
    sen_no = sentence_no;
    for (int i = 0; i < sentence.size(); i++)
    {
        int ascii = static_cast<int>(sentence[i]);
        if (ascii <= 90 && ascii >= 65)
        {
            char r = static_cast<char>(ascii + 32);
            sen.push_back(r);
        }
        else
        {
            sen.push_back(sentence[i]);
        }
    }
}

vector<int> LPS(string s)
{
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
        {
            j = pi[j - 1];
        }
        if (s[i] == s[j])
        {
            j++;
        }
        pi[j] = j;
    }
    return pi;
}

vector<int> search1(vector<int> prefix_arr, vector<char> test, string pattern)
{
    vector<int> res;
    int pos = -1;
    int i = 0;
    int j = 0;
    while (i < test.size())
    {
        if (test[i] == pattern[j])
        {
            j++;
            i++;
        }
        else
        {
            if (j != 0)
            {
                j = prefix_arr[j - 1];
            }
            else
            {
                i++;
            }
        }
        if (j == pattern.size())
        {
            pos = i - pattern.size();
            res.push_back(pos);
        }
    }
    return res;
}

SearchEngine::SearchEngine()
{
    // Implement your function here
}

SearchEngine::~SearchEngine()
{
    for (int i = 0; i < texts.size(); i++)
    {
        delete texts[i];
    }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    senten *sent = new senten(book_code, page, paragraph, sentence_no, sentence);
    texts.push_back(sent);
    return;
}

Node* SearchEngine::search(string pattern, int &n_matches) {
    vector<int> prefix_arr = LPS(pattern);
    Node *head = nullptr;
    Node *current = nullptr;
    int n_mat = 0;

    for (int i = 0; i < texts.size(); i++) {
        vector<char> temp = texts[i]->sen;
        vector<int> p = search1(prefix_arr, temp, pattern);
        
        for (int k = 0; k < p.size(); k++) {
            n_mat++;
            Node *newNode = new Node(texts[i]->b_code, texts[i]->pg, texts[i]->para, texts[i]->sen_no, p[k]);
            
            if (current == nullptr) {
                head = newNode;
                current = newNode;
            } else {
                current->right = newNode;
                newNode->left = current;
                current = newNode;
            }
        }
    }

    n_matches = n_mat;
    return head;
}
