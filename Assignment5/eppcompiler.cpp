#include "eppcompiler.h"
#include <iostream>
using namespace std;

EPPCompiler::EPPCompiler()
{
    memory_size = 0;
    output_file = "";
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    memory_size = mem_limit;
    output_file = out_file;
    least_mem_loc = MinHeap();
    for (int i = 0; i < mem_limit; i++)
    {
        // mem_loc.push_back(i);
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    for (int i = 0; i < code.size(); i++)
    {
        vector<string> to_be_parsed = code[i];
        targ.parse(to_be_parsed);
        vector<string> targ_com = generate_targ_commands();
        write_to_file(targ_com);
    }
}

void rec(vector<string> &v, ExprTreeNode *rt, Parser *targ)
{
    if (rt == NULL)
    {
        return;
    }
    else if (rt->type == "VAR")
    {
        v.push_back("PUSH mem[" + to_string(targ->symtable->search(rt->id)) + "]");
    }
    else if (rt->type == "VAL")
    {
        v.push_back("PUSH " + to_string(rt->num));
    }
    else
    {
        // MUL or ADD or SUB or DIV
        // post order traversal computes right first then left because order matter in SUB and DIV
        rec(v, rt->right, targ);
        rec(v, rt->left, targ);
        v.push_back(rt->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> ans;
    ExprTreeNode *to_targ = targ.expr_trees.back();
    if (to_targ->left->type == "DEL")
    {
        // mem_loc.push_back(targ.last_deleted);
        least_mem_loc.push_heap(targ.last_deleted);
        ans.push_back("DEL = mem[" + to_string(targ.last_deleted) + "]");
    }
    else
    {
        if (to_targ->left->type == "RET")
        {
            rec(ans, to_targ->right, &targ);
            ans.push_back("RET = POP");
        }
        else
        {
            rec(ans, to_targ->right, &targ);
            // int new_address = mem_loc.back();
            // mem_loc.pop_back();
            int new_address = least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(to_targ->left->id, new_address);
            ans.push_back("mem[" + to_string(new_address) + "] = POP");
        }
    }
    return ans;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream outFile(output_file, ios::app);
    for (const string &comman : commands)
    {
        outFile << comman << endl;
    }
    outFile.close();
}

EPPCompiler::~EPPCompiler()
{
}