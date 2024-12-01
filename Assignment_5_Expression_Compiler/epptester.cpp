#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "eppcompiler.cpp"
#include "symnode.cpp"
#include "symtable.cpp"
#include "parser.cpp"
#include "exprtreenode.cpp"
#include "minheap.cpp"
#include "heapnode.cpp"

int main() {
    int ct = 0;
    vector<vector<string>> code;
    ifstream tc_file("testcase_exp.txt");
    string ln;
    while (getline(tc_file, ln)) {
        stringstream ss(ln);
        string temp;
        vector<string> toPush;
        while (getline(ss, temp, ' ')) {
            toPush.push_back(temp);
        }
        code.push_back(toPush);
        ct++;
    }

    EPPCompiler e = EPPCompiler("targ.txt", ct);
    ofstream writer("targ.txt");
    writer.close();
    e.compile(code);
    tc_file.close();
    return 0;
}