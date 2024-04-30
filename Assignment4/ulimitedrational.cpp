/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
using namespace std;

int is_bigger_modnew(UnlimitedInt *i1, UnlimitedInt *i2)
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

UnlimitedInt *gcd(UnlimitedInt *a, UnlimitedInt *b)
{
    if (b->get_sign() == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(a->get_array(), a->get_capacity(), a->get_sign(), a->get_size());
        return temp;
    }
    else
    {
        if (is_bigger_modnew(a, b) == -1)
        {
            return gcd(b, a);
        }
        else
        {
            UnlimitedInt *amodb = UnlimitedInt::mod(a, b);
            UnlimitedInt *ans = gcd(b, amodb);
            delete amodb;
            return ans;
        }
    }
}

UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt();
    q = new UnlimitedInt();
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if (num->get_sign() == 1 && den->get_sign() == -1)
    {
        p = new UnlimitedInt(num->get_array(), num->get_capacity(), -1, num->get_size());
        q = new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size());
    }
    else if (num->get_sign() == -1 && den->get_sign() == -1)
    {
        p = new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size());
        q = new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size());
    }
    else if (den->get_sign() == 0)
    {
        p = new UnlimitedInt();
        q = new UnlimitedInt();
    }
    else
    {

        p = new UnlimitedInt(num->get_array(), num->get_capacity(), num->get_sign(), num->get_size());
        q = new UnlimitedInt(den->get_array(), den->get_capacity(), den->get_sign(), den->get_size());
    }
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    string a = p->to_string();
    string b = q->to_string();
    string ans = a + "/" + b;
    return ans;
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *q2 = i2->get_q();
    if (p1->get_sign() == 0)
    {
        UnlimitedRational *temp = new UnlimitedRational(p2, q2);
        return temp;
    }
    else if (p2->get_sign() == 0)
    {
        UnlimitedRational *temp = new UnlimitedRational(p1, q1);
        return temp;
    }
    else
    {
        UnlimitedInt *temp1 = UnlimitedInt::mul(p1, q2);
        UnlimitedInt *temp2 = UnlimitedInt::mul(p2, q1);
        UnlimitedInt *temp3 = UnlimitedInt::add(temp1, temp2);
        UnlimitedInt *temp4 = UnlimitedInt::mul(q1, q2);
        UnlimitedInt *temp5 = new UnlimitedInt(temp3->get_array(), temp3->get_capacity(), 1, temp3->get_size());
        UnlimitedInt *temp6 = new UnlimitedInt(temp4->get_array(), temp4->get_capacity(), 1, temp4->get_size());
        UnlimitedInt *gcdpq = gcd(temp5, temp6);
        delete temp5;
        delete temp6;
        UnlimitedInt *newp = UnlimitedInt::div(temp3, gcdpq);
        UnlimitedInt *newq = UnlimitedInt::div(temp4, gcdpq);
        UnlimitedRational *ans = new UnlimitedRational(newp, newq);
        delete temp1;
        delete temp2;
        delete temp3;
        delete temp4;
        delete gcdpq;
        delete newp;
        delete newq;
        return ans;
    }
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *temp = new UnlimitedInt(i2->get_p()->get_array(), i2->get_p()->get_capacity(), (-1) * i2->get_p()->get_sign(), i2->get_p()->get_size());
    UnlimitedRational *r2 = new UnlimitedRational(temp, i2->get_q());
    UnlimitedRational *ans = UnlimitedRational::add(i1, r2);
    delete temp;
    delete r2;
    return ans;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_q()->get_sign() == 0 || i2->get_q()->get_sign() == 0)
    {
        UnlimitedRational *temp = new UnlimitedRational();
        return temp;
    }
    else if (i1->get_p()->get_sign() == 0 || i2->get_p()->get_sign() == 0)
    {
        UnlimitedInt *zero = new UnlimitedInt(0);
        UnlimitedInt *one = new UnlimitedInt(1);
        UnlimitedRational *temp = new UnlimitedRational(zero, one);
        delete zero;
        delete one;
        return temp;
    }
    else
    {
        UnlimitedInt *temp1 = UnlimitedInt::mul(i1->get_p(), i2->get_p());
        UnlimitedInt *temp2 = UnlimitedInt::mul(i1->get_q(), i2->get_q());

        UnlimitedInt *temp3 = new UnlimitedInt(temp1->get_array(), temp1->get_capacity(), 1, temp1->get_size());
        UnlimitedInt *temp4 = new UnlimitedInt(temp2->get_array(), temp2->get_capacity(), 1, temp2->get_size());
        UnlimitedInt *gcdpq = gcd(temp3, temp4);
        delete temp3;
        delete temp4;
        UnlimitedInt *newp = UnlimitedInt::div(temp1, gcdpq);
        UnlimitedInt *newq = UnlimitedInt::div(temp2, gcdpq);
        delete temp1;
        delete temp2;
        UnlimitedRational *ans = new UnlimitedRational(newp, newq);
        delete newp;
        delete newq;
        return ans;
    }
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_q()->get_sign() == 0 || i2->get_p()->get_sign() == 0 || i2->get_q()->get_sign() == 0)
    {
        UnlimitedRational *temp = new UnlimitedRational();
        return temp;
    }
    else if (i1->get_p()->get_sign() == 0)
    {
        UnlimitedInt *zero = new UnlimitedInt(0);
        UnlimitedInt *one = new UnlimitedInt(1);
        UnlimitedRational *temp = new UnlimitedRational(zero, one);
        delete zero;
        delete one;
        return temp;
    }
    else
    {
        UnlimitedInt *temp1 = UnlimitedInt::mul(i1->get_p(), i2->get_q());
        UnlimitedInt *temp2 = UnlimitedInt::mul(i1->get_q(), i2->get_p());

        UnlimitedInt *temp3 = new UnlimitedInt(temp1->get_array(), temp1->get_capacity(), 1, temp1->get_size());
        UnlimitedInt *temp4 = new UnlimitedInt(temp2->get_array(), temp2->get_capacity(), 1, temp2->get_size());
        UnlimitedInt *gcdpq = gcd(temp3, temp4);
        delete temp3;
        delete temp4;
        UnlimitedInt *newp = UnlimitedInt::div(temp1, gcdpq);
        UnlimitedInt *newq = UnlimitedInt::div(temp2, gcdpq);
        delete temp1;
        delete temp2;
        UnlimitedRational *ans = new UnlimitedRational(newp, newq);
        delete newp;
        delete newq;
        return ans;
    }
}