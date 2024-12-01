#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
using namespace std;

class para_node
{
public:
    int book_code;
    int page;
    int paragraph;
    double score;
    Dict *para_dict;
    para_node(int book_code, int page, int paragraph);
    ~para_node();
};

class QNA_tool
{
public:
    Dict *corpus;
    vector<para_node *> p_dict;
    vector<double> docLengths;

    QNA_tool();
    ~QNA_tool();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *get_top_k_para(string question, int k);

    std::string get_paragraph(int book_code, int page, int paragraph);

    void query(string question);

    double IDF(const string &term, vector<pair<string, double>> &idf, vector<pair<string, double>> &docFreq);
    void score(const vector<string> &query, vector<para_node *> &p_dict, vector<pair<string, double>> &idf, vector<pair<string, double>> &docFreq);
    Node *get_top_k_para_2(string question, int k);

    void query_llm(string filename, Node *root, int k, string API_KEY, string question);
    void query_llm_hugchat(string filename, Node *root, int k, string question);
};