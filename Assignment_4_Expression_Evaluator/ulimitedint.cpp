/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;

int is_bigger_mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() > i2->get_size())
    {
        return 1;
    }
    else if (i1->get_size() < i2->get_size())
    {
        return -1;
    }
    else
    {
        int *a = i1->get_array();
        int *b = i2->get_array();
        for (int i = 0; i < i1->get_size(); i++)
        {
            if (a[i] > b[i])
            {
                return 1;
            }
            else if (a[i] < b[i])
            {
                return -1;
            }
        }
        return 0;
    }
}

UnlimitedInt::UnlimitedInt()
{
    size = 1;
    sign = 0;
    capacity = size;
    unlimited_int = new int[size]{};
}

UnlimitedInt::UnlimitedInt(string s)
{
    if (s.size() == 0 || s[0] == '0')
    {
        size = 1;
        sign = 0;
        capacity = size;
        unlimited_int = new int[size]{};
    }
    else
    {
        if (s[0] == '-')
        {
            size = s.size() - 1;
            sign = -1;
            capacity = size;
            unlimited_int = new int[size];
            for (int i = 0; i < size; i++)
            {
                unlimited_int[i] = int(s[i + 1]) - 48;
            }
        }
        else
        {
            size = s.size();
            sign = +1;
            capacity = size;
            unlimited_int = new int[size];
            for (int i = 0; i < size; i++)
            {
                unlimited_int[i] = int(s[i]) - 48;
            }
        }
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    int x = i;
    if (x == 0)
    {
        size = 1;
        sign = 0;
        capacity = size;
        unlimited_int = new int[size]{};
    }
    else if (x < 0)
    {
        sign = -1;
        if (x == -2147483648)
        {
            size = 10;
            unlimited_int = new int[size]{2, 1, 4, 7, 4, 8, 3, 6, 4, 8};
        }
        else
        {
            x = -x;
            size = 0;
            int y = x;
            while (y > 0)
            {
                size++;
                y = y / 10;
            }
            unlimited_int = new int[size];
            for (int i = size - 1; i >= 0; i--)
            {
                unlimited_int[i] = x % 10;
                x = x / 10;
            }
        }
        capacity = size;
    }
    else
    {
        sign = +1;
        size = 0;
        int y = x;
        while (y > 0)
        {
            size++;
            y = y / 10;
        }
        unlimited_int = new int[size];
        for (int i = size - 1; i >= 0; i--)
        {
            unlimited_int[i] = x % 10;
            x = x / 10;
        }
        capacity = size;
    }
}

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    size = sz;
    sign = sgn;
    capacity = cap;
    unlimited_int = new int[size];
    for (int i = 0; i < size; i++)
    {
        unlimited_int[i] = ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}

int UnlimitedInt::get_size()
{
    return size;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_sign() == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(i2->get_array(), i2->get_capacity(), i2->get_sign(), i2->get_size());
        return temp;
    }
    else if (i2->get_sign() == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(i1->get_array(), i1->get_capacity(), i1->get_sign(), i1->get_size());
        return temp;
    }
    else if ((i1->get_sign() == 1 && i2->get_sign() == 1) || (i1->get_sign() == -1 && i2->get_sign() == -1))
    {
        int nsign = i1->get_sign();
        int s1, s2;
        int *a, *b;
        if (i1->get_size() > i2->get_size())
        {
            s1 = i1->get_size();
            s2 = i2->get_size();
            a = i1->get_array();
            b = i2->get_array();
        }
        else
        {
            s1 = i2->get_size();
            s2 = i1->get_size();
            a = i2->get_array();
            b = i1->get_array();
        }
        int nsize = s1 + 1;
        int *narray = new int[nsize]{};
        int carry = 0;

        for (int i = 0; i < s2; i++)
        {
            int x = a[s1 - i - 1] + b[s2 - i - 1] + carry;
            narray[nsize - 1 - i] = x % 10;
            carry = x / 10;
        }
        for (int i = s2; i < s1; i++)
        {
            int x = a[s1 - i - 1] + carry;
            narray[nsize - 1 - i] = x % 10;
            carry = x / 10;
        }

        if (carry != 0)
        {
            narray[0] = carry;
            UnlimitedInt *temp = new UnlimitedInt(narray, nsize, nsign, nsize);
            delete[] narray;
            return temp;
        }
        else
        {
            nsize = s1;
            int *narray2 = new int[nsize];
            for (int i = 0; i < nsize; i++)
            {
                narray2[i] = narray[i + 1];
            }
            delete[] narray;
            UnlimitedInt *temp = new UnlimitedInt(narray2, nsize, nsign, nsize);
            delete[] narray2;
            return temp;
        }
    }
    else
    {
        int big = is_bigger_mod(i1, i2);
        if (big == 0)
        {
            UnlimitedInt *temp = new UnlimitedInt();
            return temp;
        }
        else
        {
            int nsign;
            int *a, *b;
            int s1, s2;
            if (big == 1)
            {
                nsign = i1->get_sign();
                a = i1->get_array();
                s1 = i1->get_size();
                b = i2->get_array();
                s2 = i2->get_size();
            }
            else if (big == -1)
            {
                nsign = -1 * (i1->get_sign());
                a = i2->get_array();
                s1 = i2->get_size();
                b = i1->get_array();
                s2 = i1->get_size();
            }

            int nsize = s1;
            int *narray = new int[nsize]{};
            int carry = 0;

            for (int i = 0; i < s2; i++)
            {
                int x = a[s1 - i - 1] - b[s2 - i - 1] + carry;
                if (x >= 0)
                {
                    narray[nsize - 1 - i] = x;
                    carry = 0;
                }
                else
                {
                    narray[nsize - 1 - i] = x + 10;
                    carry = -1;
                }
            }
            for (int i = s2; i < s1; i++)
            {
                int x = a[s1 - i - 1] + carry;
                narray[nsize - 1 - i] = x % 10;
                if (x >= 0)
                {
                    narray[nsize - 1 - i] = x;
                    carry = 0;
                }
                else
                {
                    narray[nsize - 1 - i] = x + 10;
                    carry = -1;
                }
            }
            for (int i = 0; i < s1; i++)
            {
                if (narray[i] == 0)
                {
                    nsize--;
                }
                else
                {
                    break;
                }
            }
            int *narray2 = new int[nsize]{};
            for (int i = 0; i < nsize; i++)
            {
                narray2[nsize - i - 1] = narray[s1 - i - 1];
            }
            delete[] narray;
            UnlimitedInt *temp = new UnlimitedInt(narray2, nsize, nsign, nsize);
            delete[] narray2;
            return temp;
        }
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *temp2 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), -1 * (i2->get_sign()), i2->get_size());
    UnlimitedInt *temp = UnlimitedInt::add(i1, temp2);
    delete temp2;
    return temp;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int nsign = i1->get_sign() * i2->get_sign();
    if (nsign == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt();
        return temp;
    }
    else
    {
        int *a, *b;
        int s1, s2;
        if (i1->get_size() > i2->get_size())
        {
            a = i1->get_array();
            b = i2->get_array();
            s1 = i1->get_size();
            s2 = i2->get_size();
        }
        else
        {
            a = i2->get_array();
            b = i1->get_array();
            s1 = i2->get_size();
            s2 = i1->get_size();
        }
        int nsize = s1 + s2;
        int *narray = new int[nsize]{};
        for (int i = s1 - 1; i >= 0; i--)
        {
            for (int j = s2 - 1; j >= 0; j--)
            {
                int mul = a[i] * b[j];
                int sum = mul + narray[i + j + 1];

                narray[i + j + 1] = sum % 10;
                narray[i + j] += sum / 10;
            }
        }

        for (int i = 0; i < s1 + s2; i++)
        {
            if (narray[i] == 0)
            {
                nsize--;
            }
            else
            {
                break;
            }
        }
        int *narray2 = new int[nsize]{};
        for (int i = 0; i < nsize; i++)
        {
            narray2[nsize - i - 1] = narray[s1 + s2 - i - 1];
        }
        delete[] narray;
        UnlimitedInt *temp = new UnlimitedInt(narray2, nsize, nsign, nsize);
        delete[] narray2;
        return temp;
    }
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int nsign = i1->get_sign() * i2->get_sign();
    if (nsign == 0 || (is_bigger_mod(i1, i2) == -1 && nsign == 1))
    {
        UnlimitedInt *temp = new UnlimitedInt();
        return temp;
    }
    else if (is_bigger_mod(i1, i2) == -1 && nsign == -1)
    {
        UnlimitedInt *temp = new UnlimitedInt(-1);
        return temp;
    }
    else
    {
        UnlimitedInt *temp1 = new UnlimitedInt(i1->get_array(), i1->get_size(), 1, i1->get_size());
        UnlimitedInt *temp2 = new UnlimitedInt(i2->get_array(), i2->get_size(), 1, i2->get_size());
        UnlimitedInt *rem = new UnlimitedInt();
        UnlimitedInt *ans = new UnlimitedInt();
        UnlimitedInt *ten = new UnlimitedInt(10);
        UnlimitedInt *temp;
        UnlimitedInt *ith;
        for (int i = 0; i < i1->get_size(); i++)
        {
            temp = rem;
            rem = UnlimitedInt::mul(temp, ten);
            delete temp;
            ith = new UnlimitedInt(temp1->unlimited_int[i]);
            temp = rem;
            rem = UnlimitedInt::add(temp, ith);
            delete temp;
            delete ith;

            int x = 0;
            while (is_bigger_mod(rem, temp2) >= 0)
            {
                temp = rem;
                rem = UnlimitedInt::sub(temp, temp2);
                delete temp;
                x++;
            }
            temp = ans;
            ans = UnlimitedInt::mul(temp, ten);
            delete temp;
            temp = ans;
            UnlimitedInt *xtemp = new UnlimitedInt(x);
            ans = UnlimitedInt::add(temp, xtemp);
            delete temp;
            delete xtemp;
        }
        delete ten;
        delete temp1;
        delete temp2;
        ans->sign = nsign;

        if (nsign == -1 && rem->get_sign() == +1)
        {
            UnlimitedInt *one = new UnlimitedInt(1);
            UnlimitedInt *tempone = ans;
            ans = UnlimitedInt::sub(tempone, one);
            delete one;
            delete tempone;
        }
        delete rem;
        return ans;
    }
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *a_by_b = UnlimitedInt::div(i1, i2);
    UnlimitedInt *b_mul_a_by_b = UnlimitedInt::mul(i2, a_by_b);
    UnlimitedInt *ans = UnlimitedInt::sub(i1, b_mul_a_by_b);
    delete a_by_b;
    delete b_mul_a_by_b;
    return ans;
}

string UnlimitedInt::to_string()
{
    string ans = "";
    if (sign == 0)
    {
        ans = "0";
    }
    else
    {
        if (sign == -1)
        {
            ans = ans + "-";
        }
        for (int i = 0; i < size; i++)
        {
            ans = ans + std::to_string(unlimited_int[i]);
        }
    }
    return ans;
}