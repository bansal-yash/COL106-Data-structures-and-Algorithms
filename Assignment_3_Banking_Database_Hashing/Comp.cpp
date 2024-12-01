#include "Comp.h"
using namespace std;

Comp::Comp()
{
    bankStorage2d.resize(100019, std::vector<Account>(0));
}

void Comp::createAccount(std::string id, int count)
{
    Account temp{id, count};
    int hash_value = hash(id);
    bankStorage2d[hash_value].push_back(temp);
    database_size++;
}

std::vector<int> Comp::getTopK(int k)
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

    int a = min(k, database_size);

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

int Comp::getBalance(std::string id)
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

void Comp::addTransaction(std::string id, int count)
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
        database_size++;
    }
}

bool Comp::doesExist(std::string id)
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

bool Comp::deleteAccount(std::string id)
{
    int hash_value = hash(id);
    int a = bankStorage2d[hash_value].size();
    for (int i = 0; i < a; i++)
    {
        if (bankStorage2d[hash_value][i].id == id)
        {
            bankStorage2d[hash_value].erase(bankStorage2d[hash_value].begin() + i);
            database_size--;
            return true;
        }
    }
    return false;
}
int Comp::databaseSize()
{
    return database_size;
}

int Comp::hash(std::string id)
{
    int hash_val = 0;
    char a = id[0], b = id[1], c = id[2], d = id[3];

    hash_val += abs((a ^ b - 11) * (b ^ c + 3) * (c ^ d + 13) * (d ^ a + 7));

    int x = abs((13 * (id[12] ^ id[13] - 3) + 23 * (id[13] ^ id[14] + 11) + 31 * (id[14] ^ id[15] - 7) + 47 * (id[15] ^ id[16] + 5) + 59 * (id[16] ^ id[17] - 3) + 71 * (id[17] ^ id[18] + 13) + 73 * (id[18] ^ id[19] - 2) + 83 * (id[19] ^ id[20] + 17) + 109 * (id[20] ^ id[21] - 1) + 113 * (id[21] ^ id[12])) / 10);
    x = x * abs((5 * (id[4] ^ id[5] - 11) + 17 * (id[5] ^ id[6] + 2) + 19 * (id[6] ^ id[7] + 7) + 37 * (id[7] ^ id[8] - 3) + 41 * (id[8] ^ id[9] - 5) + 61 * (id[9] ^ id[10] + 13) + 79 * (id[10] ^ id[4] - 1)) / 10);

    hash_val += x;
    hash_val = hash_val % 100019;
    return hash_val;
}