#include <bits/stdc++.h>
#include "Node.h"
#include "qna_tool.h"

using namespace std;

int main()
{
    QNA_tool qna_tool;
    int num_books = 98;

    for (int i = 1; i <= num_books; i++)
    {
        std::cout << "Inserting book " << i << std::endl;

        std::string filename = "mahatma-gandhi-collected-works-volume-";
        filename += to_string(i);
        filename += ".txt";

        std::ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open the input file mahatma-gandhi." << std::endl;
            return 1;
        }

        std::string tuple;
        std::string sentence;

        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
        {
            tuple += ')';

            std::vector<int> metadata;
            std::istringstream iss(tuple);
            std::string token;

            iss.ignore(1);
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
                    metadata.push_back(num);
                }
                else
                {
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }

            qna_tool.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        }

        inputFile.close();
    }

    // while (true)
    // {
        string question;
        cout << "Please enter the query:- " << endl;
        getline(cin, question);
        qna_tool.query(question);
    // }

    return 0;
}