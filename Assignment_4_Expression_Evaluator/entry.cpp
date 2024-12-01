/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
using namespace std;

SymEntry::SymEntry()
{
    key = "";
    val = nullptr;
    left = nullptr;
    right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational *v)
{
    key = k;
    val = new UnlimitedRational(v->get_p(), v->get_q());
    left = nullptr;
    right = nullptr;
}

SymEntry::~SymEntry()
{
    delete val;
    delete left;
    delete right;
}