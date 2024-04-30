#include <bits/stdc++.h>
#include "dict.cpp"
#include <chrono>
#define file_ct 98
#define dump_test_freq 5
#define mode 1
#define bound 12
#define FILE "mahatma-gandhi-collected-works-volume-1.txt"

bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream input1(file1);
    std::ifstream input2(file2);
    
    std::string line1, line2;
    int lineNum = 0;

    while (std::getline(input1, line1) && std::getline(input2, line2)) {
        lineNum++;

        if (line1 != line2) {
            std::cout << "Files differ at line " << lineNum << ":\n";
            std::cout << "File 1: " << line1 << "\n";
            std::cout << "File 2: " << line2 << "\n";
            return false;
        }
    }

    // Check for differences in the number of lines
    // if (input1.eof() != input2.eof()) {
    //     std::cout << "Files have different numbers of lines.\n";
    //     return false;
    // }

    return true;
}

int main()
{
    auto total_time = chrono::high_resolution_clock::now();
    string dir = "./txtfiles/mahatma-gandhi-collected-works-volume-";
    for (int i = 1; i <= file_ct; i++)
    {
        auto str = chrono::high_resolution_clock::now();
        string FILENAME = dir + to_string(i) + ".txt";
        std::ifstream inputFile(FILENAME);

        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open the input file." << std::endl;
            return 1;
        }

        std::string tuple;
        std::string sentence;

        Dict d;

        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
        {
            // Get a line in the sentence
            tuple += ')';

            std::vector<int> metadata;
            std::istringstream iss(tuple);

            // Temporary variables for parsing
            std::string token;

            // Ignore the first character (the opening parenthesis)
            iss.ignore(1);

            // Parse and convert the elements to integers
            while (std::getline(iss, token, ','))
            {
                // Trim leading and trailing white spaces
                size_t start = token.find_first_not_of(" ");
                size_t end = token.find_last_not_of(" ");
                if (start != std::string::npos && end != std::string::npos)
                {
                    token = token.substr(start, end - start + 1);
                }

                // Check if the element is a number or a string
                if (token[0] == '\'')
                {
                    // Remove the single quotes and convert to integer
                    int num = std::stoi(token.substr(1, token.length() - 2));
                    metadata.push_back(num);
                }
                else
                {
                    // Convert the element to integer
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }

            // Now we have the string in sentence
            // And the other info in metadata
            // Add to the dictionary

            // Insert in the dictionary
            d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        }
        if (mode)
        {
            inputFile.close();

            // Get the counts of some words
            string dt = "./Output/counts_" + to_string(i) + ".txt";
            std::ifstream dict(dt.c_str());
            if (!dict.is_open())
            {
                std::cerr << "Error: Unable to open the file." << std::endl;
                return 1;
            }

            bool passed = true;
            std::string l;
            while (std::getline(dict, l))
            {
                std::istringstream iss(l);
                std::string key;
                int value;

                if (std::getline(iss, key, ',') && iss >> value)
                {
                    if (value > bound)
                    {
                        if (d.get_word_count(key) != value)
                        {
                            cout << "Expected count for word " << key << ": " << value << ", received: " << d.get_word_count(key) << endl;
                            passed = false;
                            break;
                        }
                    }
                }
            }
            if (!passed)
            {
                return 0;
            }
            if (i % 1 == 0)
            {
                cout << "Dumping for File No. :" << i << endl;
                d.dump_dictionary("test_dump.txt");


                ifstream inputFile("test_dump.txt");
                if (!inputFile) {
                    std::cerr << "Error opening the input file: " << "test_dump.txt" << std::endl;
                    continue;
                }
                vector<std::string> lines;
                string line_;
                while (getline(inputFile, line_)) {
                    lines.push_back(line_);
                }
                inputFile.close();
                std::sort(lines.begin(), lines.end());
                std::ofstream outputFile("test_dump_sorted.txt");
                if (!outputFile) {
                    std::cerr << "Error opening the output file: " << "test_dump_sorted.txt" << std::endl;
                    continue; // Skip to the next file
                }
                for (const std::string& sortedLine : lines) {
                    outputFile << sortedLine << '\n';
                }

                // string a, b;
                string cr_F = "./Output/counts_" + to_string(i) + ".txt";
                // if (!compareFiles(cr_F, "test_dump_sorted.txt", a, b))
                // {
                //     cout << "Err in Dump_dict of File :" << i << "\n Expected: " << a << "Got: " << b << "\n";
                //     return 1;
                // }
                if (compareFiles(cr_F, "test_dump_sorted.txt")) {
                std::cout << "Files are identical.\n";
            } else {
                std::cout << "Files are different.\n";
            }


            }
            dict.close();
        }
        else
        {
            d.dump_dictionary("counts.txt");
            string temp = "sort counts.txt > ./Output/counts_" + to_string(i) + ".txt";
            system(temp.c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto time_taken = chrono::duration_cast<chrono::microseconds>(end - str);
        cout << "Passed Test for File No.:" << i << "\nTime Taken:" << time_taken.count() << " us\n";
        if (i == file_ct)
        {

            cout << "\n\nTotal_time:" << chrono::duration_cast<chrono::microseconds>(end - total_time).count() << "\n";
        }
    }
    return 0;
}
