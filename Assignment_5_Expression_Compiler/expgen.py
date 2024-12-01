import random as r
import string
from os import sys

sys.set_int_max_str_digits(10000)

class Stack():
    def __init__(self):
        self.stk = []
    def push(self, x):
        self.stk.append(x)
    def pop(self):
        if (len(self.stk) == 0):
            raise RuntimeError("Pop tried to pop from empty stack!")
        return self.stk.pop()

max_int = 100 #max value of integer in an exp
num_testcases = 1000 #max num of lines in a program
max_exp_length = 30
percent_ret = 1
symT = []

def mergeExp(L):
    if (len(L) == 1):
        return " " + str(L[0]) + " "
    n = len(L)//2
    L1 = L[:n]
    L2 = L[n:]
    s1 = mergeExp(L1)
    s2 = mergeExp(L2)
    return " (" + s1 + r.choice(["+","-","*","+","-","*","+","-","*","+","-","*","+","-","*","+","-","*","/"]) + s2 + ") "

def randList():
    ct = r.randint(1, max_exp_length)
    L = []
    for i in range(ct):
        if len(L) > 0:
            t = r.randint(1, 2)
            if len(symT) == 0: t = 1
            if (t == 1):
                L.append(r.randint(1, max_int))
            elif (t == 2):
                L.append(r.choice(symT))
        else:
            L.append(r.randint(1, max_int))
    return L

def compute(s):
    s = s.replace("/", "//")
    x = s.split()
    for i in range(len(x)):
        if x[i] in symT:
            x[i] = str(symT[x[i]])
    if "NULL" in x: ret = "NULL"
    else:
        try:
            ret = eval("".join(x))
        except ZeroDivisionError:
            ret = "NULL"
    return ret

def vName():
    l = r.randint(1, 6)
    s = ''.join(r.choices(string.ascii_lowercase + "_", k=1))
    for i in range(1, l):
        s += ''.join(r.choices(string.ascii_lowercase + string.digits + "_", k=1))
    return s

to_write = []
i = 0
if input("Generate mode(1) or check TARG mode(2)?: ") == "2":
    with open("targ.txt", "r") as F:
        to_read = F.readlines()
    with open("testcase_exp.txt", "r") as F:
        to_compute = F.readlines()
    symT = {}
    for i in to_compute:
        x = i.strip().split()
        if i[:3] == "ret":
            ans = compute(" ".join(x[2:]))
            break
        elif i[:3] == "del":
            del symT[x[2]]
        else:
            symT[x[0]] = compute(" ".join(x[2:]))

    mem = {}
    S = Stack()
    for i in to_read:
        x = i.strip().split()
        if x[0] == "PUSH":
            if (x[1][0] == "m"):
                S.push(mem[x[1][4:-1]])
            else: S.push(int(x[1]))
        elif x[0] == "DEL":
            del mem[x[2][4:-1]]
        elif x[0] == "ADD":
            a = S.pop()
            b = S.pop()
            if (a == "NULL") or (b == "NULL"): c = "NULL"
            else: c = a + b
            S.push(c)
        elif x[0] == "SUB":
            a = S.pop()
            b = S.pop()
            if (a == "NULL") or (b == "NULL"): c = "NULL"
            else: c = a - b
            S.push(c)
        elif x[0] == "MUL":
            a = S.pop()
            b = S.pop()
            if (a == "NULL") or (b == "NULL"): c = "NULL"
            else: c = a * b
            S.push(c)
        elif x[0] == "DIV":
            a = S.pop()
            b = S.pop()
            if (a == "NULL") or (b == "NULL") or (b == 0): c = "NULL"
            else: c = a // b
            S.push(c)
        elif x[0] == "RET":
            t = S.pop()
            if t == ans:
                print("Correct! Answer is", str(ans))
                break
            else:
                print("Wrong! Answer given:", str(t), "but actual answer is", str(ans))
        else:
            mem[x[0][4:-1]] = S.pop()
            
            
else:
    while i < num_testcases:
        op = r.randint(1, percent_ret*100)
        if (op == 1):
            to_write.append("ret :=" + mergeExp(randList()) + "\n")
            break
        if (op % 5 == 0):
            if len(symT) == 0:
                continue
            v = r.choice(symT)
            to_write.append("del := " + v + "\n")
            symT.remove(v)
        if (op % 5 != 0):
            t = r.randint(1, 10)
            if len(symT) == 0: t = 1
            if t > 7:
                x = r.choice(symT)
            else:
                x = vName()
                while (x in symT):
                    x = vName()
            to_write.append(x + " :=" + mergeExp(randList()) + "\n")
            if x not in symT:
                symT.append(x)
        i += 1
    else:
        to_write.append("ret :=" + mergeExp(randList()) + "\n")

    with open("testcase_exp.txt", "w") as F:
        F.writelines(to_write)
