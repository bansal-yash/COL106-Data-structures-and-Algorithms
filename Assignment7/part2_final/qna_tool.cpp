#include <assert.h>
#include <sstream>
#include <cmath>
#include "qna_tool.h"

using namespace std;

para_node::para_node(int b_code, int pag, int para)
{
    score = 0.0;
    book_code = b_code;
    page = pag;
    paragraph = para;
    para_dict = new Dict(11);
}

para_node::~para_node()
{
    delete para_dict;
}

QNA_tool::QNA_tool()
{
    corpus = new Dict(10007);
}

QNA_tool::~QNA_tool()
{
    delete corpus;
    for (int i = 0; i < (int)p_dict.size(); i++)
    {
        delete p_dict[i];
    }
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    static int parawordcnt;
    if (p_dict.size() != 0 && (p_dict.back()->book_code == book_code && p_dict.back()->page == page && p_dict.back()->paragraph == paragraph))
    {
        p_dict.back()->para_dict->insert_sentence(book_code, page, paragraph, sentence_no, sentence);
        string temp = "";
        int sz = sentence.size();

        for (int i = 0; i <= sz; i++)
        {
            int ascii = -1;
            if (i != sz)
            {
                ascii = static_cast<int>(sentence[i]);
            }
            if (i == sz || sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == ',' || sentence[i] == '-' ||
                sentence[i] == ':' || sentence[i] == '!' || sentence[i] == '"' || sentence[i] == '\'' || sentence[i] == '(' || sentence[i] == ')' ||
                sentence[i] == ';' || sentence[i] == '@' || sentence[i] == '[' || sentence[i] == ']' || sentence[i] == '?')
            {
                if (temp != "")
                {
                    parawordcnt++;
                    temp = "";
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (ascii <= 90 && ascii >= 65)
                {
                    char r = static_cast<char>(ascii + 32);
                    temp += r;
                }
                else
                {
                    char r = static_cast<char>(ascii);
                    temp += r;
                }
            }
        }
    }
    else
    {
        if (p_dict.size() != 0)
        {
            docLengths.push_back(parawordcnt);
        }
        parawordcnt = 0;
        para_node *temp = new para_node(book_code, page, paragraph);
        temp->para_dict->insert_sentence(book_code, page, paragraph, sentence_no, sentence);
        p_dict.push_back(temp);
    }
    return;
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    Node *head;
    Node *prev;
    vector<pair<string, long double>> words;
    string temp = "";
    int sz = question.size();

    for (int i = 0; i <= sz; i++)
    {
        int ascii = -1;
        if (i != sz)
        {
            ascii = static_cast<int>(question[i]);
        }
        if (i == sz || question[i] == ' ' || question[i] == '.' || question[i] == ',' || question[i] == '-' ||
            question[i] == ':' || question[i] == '!' || question[i] == '"' || question[i] == '\'' || question[i] == '(' || question[i] == ')' ||
            question[i] == ';' || question[i] == '@' || question[i] == '[' || question[i] == ']' || question[i] == '?')
        {
            if (temp != "")
            {
                words.push_back({temp, 0.0});
                temp = "";
            }
            else
            {
                continue;
            }
        }
        else
        {
            if (ascii <= 90 && ascii >= 65)
            {
                char r = static_cast<char>(ascii + 32);
                temp += r;
            }
            else
            {
                char r = static_cast<char>(ascii);
                temp += r;
            }
        }
    }

    string line;
    std::ifstream inputFile("unigram_freq.csv");

    for (int i = 0; i < (int)words.size(); i++)
    {
        getline(inputFile, line);
        bool isfound = false;
        double num = corpus->get_word_count(words[i].first) + 1;
        while (getline(inputFile, line))
        {
            string word;
            long long count;
            double den = 1.0;
            std::stringstream lineStream(line);
            std::getline(lineStream, word, ',');
            lineStream >> count;
            if (word == words[i].first)
            {
                den += (double)count;
                words[i].second = 1000000 * (num / den);
                isfound = true;
                break;
            }
        }
        if (isfound == false)
        {
            words[i].second = num;
        }
        inputFile.seekg(0, std::ios::beg);
    }

    inputFile.close();

    int siz = p_dict.size();
    for (int t = 0; t < siz; t++)
    {
        para_node *temp_para = p_dict[t];
        double temp_score = 0;
        for (int y = 0; y < (int)words.size(); y++)
        {
            int t = temp_para->para_dict->get_word_count(words[y].first);
            temp_score += t * words[y].second;
        }
        temp_para->score = temp_score;
    }

    for (int i = (siz / 2) - 1; i >= 0; i--)
    {
        int to_heapify = i;
        while (true)
        {
            int l = 2 * to_heapify + 1;
            int r = 2 * to_heapify + 2;
            if (l >= siz)
            {
                break;
            }
            else if (r >= siz)
            {
                if (p_dict[to_heapify]->score < p_dict[l]->score)
                {
                    para_node *temp = p_dict[to_heapify];
                    p_dict[to_heapify] = p_dict[l];
                    p_dict[l] = temp;
                    to_heapify = l;
                }
                else
                {
                    break;
                }
            }
            else
            {
                int a = p_dict[to_heapify]->score;
                int b = p_dict[l]->score;
                int c = p_dict[r]->score;
                if ((a > b) && (a > c))
                {
                    break;
                }
                else
                {
                    if (b > c)
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[l];
                        p_dict[l] = temp;
                        to_heapify = l;
                    }
                    else
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[r];
                        p_dict[r] = temp;
                        to_heapify = r;
                    }
                }
            }
        }
    }

    int lastelemindex = siz - 1;

    for (int t = 0; t < k; t++)
    {
        Node *newnode = new Node(p_dict[0]->book_code, p_dict[0]->page, p_dict[0]->paragraph, 0, 0);
        newnode->left = nullptr;
        newnode->right = nullptr;
        if (t == 0)
        {
            head = newnode;
            prev = newnode;
        }
        else
        {
            prev->right = newnode;
            newnode->left = prev;
            prev = newnode;
        }
        para_node *tp = p_dict[0];
        p_dict[0] = p_dict[lastelemindex];
        p_dict[lastelemindex] = tp;
        lastelemindex--;
        int to_heapify = 0;
        while (true)
        {
            int l = 2 * to_heapify + 1;
            int r = 2 * to_heapify + 2;
            if (l >= lastelemindex + 1)
            {
                break;
            }
            else if (r >= lastelemindex + 1)
            {
                if (p_dict[to_heapify]->score < p_dict[l]->score)
                {
                    para_node *temp = p_dict[to_heapify];
                    p_dict[to_heapify] = p_dict[l];
                    p_dict[l] = temp;
                    to_heapify = l;
                }
                else
                {
                    break;
                }
            }
            else
            {
                int a = p_dict[to_heapify]->score;
                int b = p_dict[l]->score;
                int c = p_dict[r]->score;
                if ((a > b) && (a > c))
                {
                    break;
                }
                else
                {
                    if (b > c)
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[l];
                        p_dict[l] = temp;
                        to_heapify = l;
                    }
                    else
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[r];
                        p_dict[r] = temp;
                        to_heapify = r;
                    }
                }
            }
        }
    }

    for (int t = 0; t < siz; t++)
    {
        p_dict[t]->score = 0.0;
    }
    return head;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph)
{
    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;

    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);
        std::string token;
        iss.ignore(1);
        int idx = 0;
        while (std::getline(iss, token, ','))
        {
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos)
            {
                token = token.substr(start, end - start + 1);
            }

            if (token[0] == '\'')
            {
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            }
            else
            {
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if (
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph))
        {
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query(string question)
{
    int a, b, k;
    Node *temp;
    cout << "Enter 1 for lousy algorithm  // Enter 2 for an awesome algorithm" << endl;
    cin >> a;
    cout << "Enter number of paragraphs:- " << endl;
    cin >> k;
    if (a == 1)
    {
        temp = get_top_k_para(question, k);
    }
    else if (a == 2)
    {
        temp = get_top_k_para_2(question, k);
    }
    else
    {
        cout << "You've reached the corner of the world, crawl back!!" << endl;
        return;
    }

    cout << "Enter 1 for chat-gpt api  // Enter 2 for the hugchat api" << endl;
    cin >> b;
    if (b == 1)
    {
        query_llm("api_call.py", temp, k, "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", question);
    }
    else if (b == 2)
    {
        query_llm_hugchat("api_hugchat.py", temp, k, question);
    }
    else
    {
        cout << "You've reached the corner of the world, crawl back!!" << endl;
        return;
    }

    if (temp->right == nullptr)
    {
        delete temp;
        return;
    }
    while (temp != nullptr)
    {
        Node *dummy = temp->right;
        delete temp;
        temp = dummy;
    }
    return;
}

Node *QNA_tool::get_top_k_para_2(string question, int k)
{
    Node *head;
    Node *prev;
    vector<pair<string, double>> idf;
    vector<pair<string, double>> docFreq;
    vector<string> query_vector;
    vector<string> documents;
    string temp = "";
    int sz = question.size();

    for (int i = 0; i <= sz; i++)
    {
        int ascii = -1;
        if (i != sz)
        {
            ascii = static_cast<int>(question[i]);
        }
        if (i == sz || question[i] == ' ' || question[i] == '.' || question[i] == ',' || question[i] == '-' ||
            question[i] == ':' || question[i] == '!' || question[i] == '"' || question[i] == '\'' || question[i] == '(' || question[i] == ')' ||
            question[i] == ';' || question[i] == '@' || question[i] == '[' || question[i] == ']' || question[i] == '?')
        {
            if (temp != "")
            {
                idf.push_back({temp, -1.0});
                docFreq.push_back({temp, 0.0});
                query_vector.push_back(temp);
                temp = "";
            }
            else
            {
                continue;
            }
        }
        else
        {
            if (ascii <= 90 && ascii >= 65)
            {
                char r = static_cast<char>(ascii + 32);
                temp += r;
            }
            else
            {
                char r = static_cast<char>(ascii);
                temp += r;
            }
        }
    }
    score(query_vector, p_dict, idf, docFreq);
    int siz = p_dict.size();
    for (int i = (siz / 2) - 1; i >= 0; i--)
    {
        int to_heapify = i;
        while (true)
        {
            int l = 2 * to_heapify + 1;
            int r = 2 * to_heapify + 2;
            if (l >= siz)
            {
                break;
            }
            else if (r >= siz)
            {
                if (p_dict[to_heapify]->score < p_dict[l]->score)
                {
                    para_node *temp = p_dict[to_heapify];
                    p_dict[to_heapify] = p_dict[l];
                    p_dict[l] = temp;
                    to_heapify = l;
                }
                else
                {
                    break;
                }
            }
            else
            {
                int a = p_dict[to_heapify]->score;
                int b = p_dict[l]->score;
                int c = p_dict[r]->score;
                if ((a > b) && (a > c))
                {
                    break;
                }
                else
                {
                    if (b > c)
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[l];
                        p_dict[l] = temp;
                        to_heapify = l;
                    }
                    else
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[r];
                        p_dict[r] = temp;
                        to_heapify = r;
                    }
                }
            }
        }
    }

    int lastelemindex = siz - 1;

    for (int t = 0; t < k; t++)
    {
        Node *newnode = new Node(p_dict[0]->book_code, p_dict[0]->page, p_dict[0]->paragraph, 0, 0);
        newnode->left = nullptr;
        newnode->right = nullptr;
        if (t == 0)
        {
            head = newnode;
            prev = newnode;
        }
        else
        {
            prev->right = newnode;
            newnode->left = prev;
            prev = newnode;
        }
        para_node *tp = p_dict[0];
        p_dict[0] = p_dict[lastelemindex];
        p_dict[lastelemindex] = tp;
        lastelemindex--;
        int to_heapify = 0;
        while (true)
        {
            int l = 2 * to_heapify + 1;
            int r = 2 * to_heapify + 2;
            if (l >= lastelemindex + 1)
            {
                break;
            }
            else if (r >= lastelemindex + 1)
            {
                if (p_dict[to_heapify]->score < p_dict[l]->score)
                {
                    para_node *temp = p_dict[to_heapify];
                    p_dict[to_heapify] = p_dict[l];
                    p_dict[l] = temp;
                    to_heapify = l;
                }
                else
                {
                    break;
                }
            }
            else
            {
                int a = p_dict[to_heapify]->score;
                int b = p_dict[l]->score;
                int c = p_dict[r]->score;
                if ((a > b) && (a > c))
                {
                    break;
                }
                else
                {
                    if (b > c)
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[l];
                        p_dict[l] = temp;
                        to_heapify = l;
                    }
                    else
                    {
                        para_node *temp = p_dict[to_heapify];
                        p_dict[to_heapify] = p_dict[r];
                        p_dict[r] = temp;
                        to_heapify = r;
                    }
                }
            }
        }
    }

    for (int t = 0; t < siz; t++)
    {
        p_dict[t]->score = 0.0;
    }
    return head;
}

double QNA_tool::IDF(const string &term, vector<pair<string, double>> &idf, vector<pair<string, double>> &docFreq)
{
    for (int i = 0; i < (int)idf.size(); i++)
    {
        if (idf[i].first == term && idf[i].second < -0.5)
        {
            double docsWithTerm = docFreq[i].second;
            idf[i].second = log((docLengths.size() - docsWithTerm + 0.5) / (docsWithTerm + 0.5) + 1.0);
        }
        if (idf[i].first == term)
        {
            return idf[i].second;
        }
    }
    return -1;
}

void QNA_tool::score(const vector<string> &query, vector<para_node *> &p_dict, vector<pair<string, double>> &idf, vector<pair<string, double>> &docFreq)
{
    double k1 = 1.5;
    double b;
    cout << "Enter the parameter b:- " << endl;
    cin >> b;
    double averageDocLength = 0.0;
    for(int i = 0; i < (int)p_dict.size(); i++){
        for(int j = 0; j < query.size(); j++){
            if(p_dict[i]->para_dict->get_word_count(query[j]) > 0){
                docFreq[j].second += 1.0;
            }
        }
    }
    for (int j = 0; j < (int)docLengths.size(); j++)
    {
        averageDocLength += docLengths[j];
    }
    averageDocLength /= docLengths.size();
    for (int i = 0; i < (int)p_dict.size(); i++)
    {
        double score = 0.0;
        for (const auto &term : query)
        {
            double f = p_dict[i]->para_dict->get_word_count(term);
            double idf_val = IDF(term, idf, docFreq);
            score += idf_val * (f * (k1 + 1.0)) / (f + k1 * (1.0 - b + b * docLengths[i] / averageDocLength));
        }
        p_dict[i]->score = score;
    }
}

void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY, string question)
{
    Node *traverse = root;
    int num_paragraph = 0;
    while (num_paragraph < k)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";

        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    ofstream outfile("query.txt");
    outfile << "These are the excerpts from mahatma gandhi's books.\nOn the basis of these, ";
    outfile << question;
    outfile.close();

    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}

void QNA_tool::query_llm_hugchat(string filename, Node *root, int k, string question)
{
    Node *traverse = root;
    int num_paragraph = 0;

    while (num_paragraph < k)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";

        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    ofstream outfile("query.txt");
    outfile << "These are the excerpts from mahatma gandhi's books.\nOn the basis of these, ";
    outfile << question;
    outfile.close();

    string command = "python3 ";
    command += filename;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}