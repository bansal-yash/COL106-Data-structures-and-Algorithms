#include "Chaining.h"
using namespace std;

Chaining::Chaining()
{
    bankStorage2d.resize(11371, std::vector<Account>(0));
}

void Chaining::createAccount(std::string id, int count)
{
    Account temp{id, count};
    int hash_value = hash(id);
    bankStorage2d[hash_value].push_back(temp);
    databasesize++;
}

std::vector<int> Chaining::getTopK(int k)
{
    vector<int> ans;
    vector<int> all_bal;

    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            all_bal.push_back(bankStorage2d[i][j].balance);
        }
    }

    int a = min(k, databasesize);

    for (int i = 0; i < a; i++)
    {
        int temp = all_bal[0];
        for (int j = 1; j < all_bal.size(); j++)
        {
            temp = max(temp, all_bal[j]);
        }
        ans.push_back(temp);

        for (int j = 0; j < all_bal.size(); j++)
        {
            if (all_bal[j] == temp)
            {
                all_bal.erase(all_bal.begin() + j);
                break;
            }
        }
    }
    return ans;
}

int Chaining::getBalance(std::string id)
{
    int hash_value = hash(id);
    int a = bankStorage2d[hash_value].size();
    for (int i = 0; i < a; i++)
    {
        if (bankStorage2d[hash_value][i].id == id)
        {
            return bankStorage2d[hash_value][i].balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count)
{
    int hash_value = hash(id);
    int a = bankStorage2d[hash_value].size();
    bool found = false;
    for (int i = 0; i < a; i++)
    {
        if (bankStorage2d[hash_value][i].id == id)
        {
            found = true;
            bankStorage2d[hash_value][i].balance += count;
            break;
        }
    }

    if (!found)
    {
        Account temp{id, count};
        bankStorage2d[hash_value].push_back(temp);
        databasesize++;
    }
}

bool Chaining::doesExist(std::string id)
{
    int hash_value = hash(id);
    int a = bankStorage2d[hash_value].size();
    for (int i = 0; i < a; i++)
    {
        if (bankStorage2d[hash_value][i].id == id)
        {
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id)
{
    int hash_value = hash(id);
    int a = bankStorage2d[hash_value].size();
    for (int i = 0; i < a; i++)
    {
        if (bankStorage2d[hash_value][i].id == id)
        {
            bankStorage2d[hash_value].erase(bankStorage2d[hash_value].begin() + i);
            databasesize--;
            return true;
        }
    }
    return false;
}
int Chaining::databaseSize()
{
    return databasesize;
}

int Chaining::hash(std::string id)
{
    int hash_val = 0;
    char a = id[0], b = id[1], c = id[2], d = id[3];

    if (a >= 'A' && a <= 'Z')
    {
        hash_val += a - 'A' + 1;
    }
    else
    {
        hash_val += a - 'a' + 1;
    }

    if (b >= 'A' && b <= 'Z')
    {
        hash_val += b - 'A' + 1;
    }
    else
    {
        hash_val += b - 'a' + 1;
    }

    if (c >= 'A' && c <= 'Z')
    {
        hash_val += c - 'A' + 1;
    }
    else
    {
        hash_val += c - 'a' + 1;
    }

    if (d >= 'A' && d <= 'Z')
    {
        hash_val += d - 'A' + 1;
    }
    else
    {
        hash_val += d - 'a' + 1;
    }
    hash_val = hash_val * 100;

    hash_val += ((id[12] - '0') + (id[13] - '0') + (id[14] - '0') + (id[15] - '0') + (id[16] - '0') + (id[17] - '0') + (id[18] - '0') + (id[19] - '0') + (id[20] - '0') + (id[21] - '0')) * 10;
    hash_val += (id[4] - '0') + (id[5] - '0') + (id[6] - '0') + (id[7] - '0') + (id[8] - '0') + (id[9] - '0') + (id[10] - '0');
    return hash_val;
}