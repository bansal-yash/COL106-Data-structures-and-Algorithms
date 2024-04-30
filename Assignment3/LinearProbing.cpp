#include "LinearProbing.h"
using namespace std;

LinearProbing::LinearProbing()
{
    bankStorage1d.resize(m, null_account);
    database_size = 0;
}

void LinearProbing::createAccount(std::string id, int count)
{
    Account temp{id, count};
    int hash_value = hash(id);

    while (bankStorage1d[hash_value].id != "NULL" && bankStorage1d[hash_value].id != "DEL")
    {
        hash_value = (hash_value + 1) % m;
    }

    bankStorage1d[hash_value] = temp;
    database_size++;
}

std::vector<int> LinearProbing::getTopK(int k)
{
    vector<int> ans;
    vector<int> all_bal;

    for (int i = 0; i < m; i++)
    {
        if (bankStorage1d[i].id != "NULL" && bankStorage1d[i].id != "DEL")
        {
            all_bal.push_back(bankStorage1d[i].balance);
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

int LinearProbing::getBalance(std::string id)
{
    int hash_value = hash(id);
    int i = 0;
    while (bankStorage1d[hash_value].id != "NULL" && i < m)
    {
        if (bankStorage1d[hash_value].id == id)
        {
            return bankStorage1d[hash_value].balance;
        }
        else
        {
            hash_value = (hash_value + 1) % m;
            i++;
        }
    }

    return -1;
}

void LinearProbing::addTransaction(std::string id, int count)
{
    int hash_value = hash(id);
    bool found = false;
    int i = 0;

    while (bankStorage1d[hash_value].id != "NULL" && i < m)
    {
        if (bankStorage1d[hash_value].id == id)
        {
            bankStorage1d[hash_value].balance += count;
            found = true;
            break;
        }
        else
        {
            hash_value = (hash_value + 1) % m;
            i++;
        }
    }

    if (!found)
    {
        createAccount(id, count);
    }
}

bool LinearProbing::doesExist(std::string id)
{
    int hash_value = hash(id);
    int i = 0;

    while (bankStorage1d[hash_value].id != "NULL" && i < m)
    {
        if (bankStorage1d[hash_value].id == id)
        {
            return true;
        }
        else
        {
            hash_value = (hash_value + 1) % m;
            i++;
        }
    }

    return false;
}

bool LinearProbing::deleteAccount(std::string id)
{
    int hash_value = hash(id);
    int i = 0;
    while (bankStorage1d[hash_value].id != "NULL" && i < m)
    {
        if (bankStorage1d[hash_value].id == id)
        {
            bankStorage1d[hash_value].id = "DEL";
            bankStorage1d[hash_value].balance = 0;
            database_size--;
            return true;
        }
        else
        {
            hash_value = (hash_value + 1) % m;
            i++;
        }
    }

    return false;
}

int LinearProbing::databaseSize()
{
    return database_size;
}

int LinearProbing::hash(std::string id)
{
    int hash_val = 0;
    char a = id[0], b = id[1], c = id[2], d = id[3];

    hash_val += abs((a - b + 1) * (b - c + 1) * (c - d + 1) * (d - a + 1));

    int x = (id[12] - '0') + (id[13] - '0') + (id[14] - '0') + (id[15] - '0') + (id[16] - '0') + (id[17] - '0') + (id[18] - '0') + (id[19] - '0') + (id[20] - '0') + (id[21] - '0');
    x = x * ((id[4] - '0') + (id[5] - '0') + (id[6] - '0') + (id[7] - '0') + (id[8] - '0') + (id[9] - '0') + (id[10] - '0'));

    hash_val += x * 10;
    hash_val = hash_val % m;
    return hash_val;
}