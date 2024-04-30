#include <iostream>
#include <vector>
using namespace std;

int linear_search(const vector<int> &v, int x)
{
    if (v.size() == 0)
    {
        return -1;
    }
    else
    {
        int a = v.size();
        for (int i = 0; i < a; i++)
        {
            if (v[i] == x)
            {
                return i;
            }
            if (v[i] > x)
            {
                return -1;
            }
        }
        return -1;
    }
}

int binary_search(const vector<int> &v, int x)
{
    int a = 0, b = v.size() - 1;
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        if (v[mid] == x)
        {
            return mid;
        }
        else if (v[mid] > x)
        {
            b = mid - 1;
        }
        else
        {
            a = mid + 1;
        }
    }
    return -1;
}

int search(const vector<int> &v, int x)
{
    if (v.size() > 100)
    {
        return binary_search(v, x);
    }
    else
    {
        return linear_search(v, x);
    }
}

int linear_search_smaller(const vector<int> &v, int x)
{
    if (v.size() == 0)
    {
        return -1;
    }
    else if (v.back() < x)
    {
        return v.size() - 1;
    }
    else
    {
        int i = 0;
        while (v[i] < x)
        {
            i = i + 1;
        }
        return i - 1;
    }
}

int binary_search_smaller(const vector<int> &v, int x)
{
    int a = 0, b = v.size() - 1;
    int ans = -1;
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        if (v[mid] > x)
        {
            b = mid - 1;
        }
        else
        {
            ans = mid;
            a = mid + 1;
        }
    }
    return ans;
}

int search_smaller(const vector<int> &v, int x)
{
    if (v.size() < 200)
    {
        return linear_search_smaller(v, x);
    }
    else
    {
        return binary_search_smaller(v, x);
    }
}

class set_structure
{
public:
    vector<int> s;
    set_structure(const vector<int> &x)
    {
        s = x;
    }
    int insert_to_set(int x)
    {
        if (belongs_to_set(x) == 0)
        {
            int temp;
            temp = search_smaller(s, x);
            s.insert(s.begin() + temp + 1, x);
        }
        return s.size();
    }
    int delete_from_set(int x)
    {
        if (belongs_to_set(x) == 1)
        {
            int temp = search(s, x);
            s.erase(s.begin() + temp);
        }
        return s.size();
    }
    int belongs_to_set(int x)
    {
        if (search(s, x) == -1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    int union_of_sets(const set_structure &set2)
    {
        vector<int> temp;
        vector<int> to_be_added = set2.s;
        int i = 0, j = 0, a = s.size(), b = to_be_added.size();
        while (i < a || j < b)
        {
            if (i < a && (j >= b || s[i] < to_be_added[j]))
            {
                temp.emplace_back(s[i]);

                i = i + 1;
            }
            else if (j < b && (i >= s.size() || s[i] > to_be_added[j]))
            {
                temp.emplace_back(to_be_added[j]);
                j = j + 1;
            }
            else
            {
                temp.emplace_back(s[i]);
                i = i + 1;
                j = j + 1;
            }
        }
        s = temp;
        return s.size();
    }
    int intersection_of_sets(const set_structure &set2)
    {
        vector<int> temp;
        vector<int> to_intersect = set2.s;
        int i = 0, j = 0, a = s.size(), b = to_intersect.size();
        while (i < a && j < b)
        {
            if (s[i] == to_intersect[j])
            {
                temp.emplace_back(s[i]);
                i = i + 1;
                j = j + 1;
            }

            else if (s[i] > to_intersect[j])
            {
                j = j + 1;
            }

            else if (s[i] < to_intersect[j])
            {
                i = i + 1;
            }
        }
        s = temp;
        return s.size();
    }
    int size_of_set()
    {
        return s.size();
    }
    int difference_of_sets(const set_structure &set2)
    {
        vector<int> temp;
        vector<int> to_subtract = set2.s;
        int i = 0, j = 0, a = s.size(), b = to_subtract.size();
        while (i < a && j < b)
        {
            if (s[i] == to_subtract[j])
            {
                i = i + 1;
                j = j + 1;
            }
            else if (s[i] > to_subtract[j])
            {
                j = j + 1;
            }
            else if (s[i] < to_subtract[j])
            {
                temp.emplace_back(s[i]);
                i = i + 1;
            }
        }
        while (i < a)
        {
            temp.emplace_back(s[i]);
            i = i + 1;
        }
        s = temp;
        return s.size();
    }
    int symmetric_difference_of_sets(const set_structure &set2)
    {
        vector<int> temp;
        vector<int> to_sym_subtract = set2.s;
        int i = 0, j = 0, a = s.size(), b = to_sym_subtract.size();
        while (i < a && j < b)
        {
            if (s[i] == to_sym_subtract[j])
            {
                i = i + 1;
                j = j + 1;
            }
            else if (s[i] > to_sym_subtract[j])
            {
                temp.emplace_back(to_sym_subtract[j]);
                j = j + 1;
            }
            else if (s[i] < to_sym_subtract[j])
            {
                temp.emplace_back(s[i]);
                i = i + 1;
            }
        }
        while (i < a)
        {
            temp.emplace_back(s[i]);
            i++;
        }
        while (j < b)
        {
            temp.emplace_back(to_sym_subtract[j]);
            j++;
        }
        s = temp;
        return s.size();
    }
    void print_set()
    {
        if (s.size() == 0)
        {
            cout << "\n";
        }
        else
        {
            int x = s.size();
            for (int i = 0; i < x - 1; i++)
            {
                cout << s[i] << ",";
            }
            cout << s[s.size() - 1] << "\n";
        }
    }
};

int main()
{
    vector<set_structure> array_of_sets;
    int num_of_sets = -1;
    int a, b, c;
    set_structure new_set({});
    while (cin >> a)
    {
        switch (a)
        {
        case 1:
            cin >> b >> c;
            if (b > num_of_sets)
            {
                new_set = set_structure({});
                array_of_sets.emplace_back(new_set);
                num_of_sets += 1;
            }
            cout << array_of_sets[b].insert_to_set(c) << "\n";
            break;
        case 2:
            cin >> b >> c;
            if (b > num_of_sets)
            {
                cout << -1 << "\n";
            }
            else
            {
                cout << array_of_sets[b].delete_from_set(c) << "\n";
            }
            break;
        case 3:
            cin >> b >> c;
            if (b > num_of_sets)
            {
                cout << -1 << "\n";
            }
            else
            {
                cout << array_of_sets[b].belongs_to_set(c) << "\n";
            }
            break;
        case 4:
            cin >> b >> c;
            if (b == c)
            {
                if (b > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                }
                cout << array_of_sets[b].size_of_set() << "\n";
            }
            else
            {
                if (b > num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 2;
                    cout << 0 << "\n";
                }
                else if (b <= num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << array_of_sets[b].size_of_set() << "\n";
                }

                else if (b > num_of_sets && c <= num_of_sets)
                {
                    new_set = set_structure(array_of_sets[c].s);
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << array_of_sets[b].size_of_set() << "\n";
                }
                else
                {
                    cout << array_of_sets[b].union_of_sets(array_of_sets[c].s) << "\n";
                }
            }
            break;
        case 5:
            cin >> b >> c;
            if (b == c)
            {
                if (b > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                }
                cout << array_of_sets[b].size_of_set() << "\n";
            }
            else
            {
                if (b > num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 2;
                    cout << 0 << "\n";
                }
                else if (b <= num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    array_of_sets[b].s = {};
                    cout << 0 << "\n";
                }
                else if (b > num_of_sets && c <= num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << 0 << "\n";
                }
                else
                {
                    cout << array_of_sets[b].intersection_of_sets(array_of_sets[c].s) << "\n";
                }
            }
            break;
        case 6:
            cin >> b;
            if (b > num_of_sets)
            {
                new_set = set_structure({});
                array_of_sets.emplace_back(new_set);
                num_of_sets += 1;
            }
            cout << array_of_sets[b].size_of_set() << "\n";
            break;
        case 7:
            cin >> b >> c;
            if (b == c)
            {
                if (b > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                }
                array_of_sets[b]
                    .s = {};
                cout << 0 << "\n";
            }
            else
            {
                if (b > num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 2;
                    cout << 0 << "\n";
                }
                else if (b <= num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << array_of_sets[b].size_of_set() << "\n";
                }
                else if (b > num_of_sets && c <= num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << 0 << "\n";
                }
                else
                {
                    cout << array_of_sets[b].difference_of_sets(array_of_sets[c].s) << "\n";
                }
            }
            break;
        case 8:
            cin >> b >> c;
            if (b == c)
            {
                if (b > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                }
                array_of_sets[b].s = {};
                cout << 0 << "\n";
            }
            else
            {
                if (b > num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 2;
                    cout << 0 << "\n";
                }
                else if (b <= num_of_sets && c > num_of_sets)
                {
                    new_set = set_structure({});
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << array_of_sets[b].size_of_set() << "\n";
                }
                else if (b > num_of_sets && c <= num_of_sets)
                {
                    new_set = set_structure(array_of_sets[c].s);
                    array_of_sets.emplace_back(new_set);
                    num_of_sets += 1;
                    cout << array_of_sets[b].size_of_set() << "\n";
                }
                else
                {
                    cout << array_of_sets[b].symmetric_difference_of_sets(array_of_sets[c].s) << "\n";
                }
            }
            break;
        case 9:
            cin >> b;
            if (b > num_of_sets)
            {
                cout << "\n";
            }
            else
            {
                array_of_sets[b].print_set();
            }
            break;
        default:
            break;
        }
    }
    return 0;
}