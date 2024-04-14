// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, int> priority {
        {'(', 0}, {')', 1}, {'-', 2}, {'+', 2}, {'/', 3}, {'*', 3}
};
TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::string infx2pstfx(std::string inf) {
    std::string str = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            str += inf[i];
            str += ' ';
        } else {
            if (inf[i] == '(' || stack1.isEmp() == 1 ||
            priority[inf[i]] > priority[stack1.get()]) {
                stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    str = str + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            } else if (priority[inf[i]] <= priority[stack1.get()]) {
                char item = stack1.pop();
                str = str + item + ' ';
                stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmp() != 1) {
        str = str + stack1.pop();
        if (stack1.isEmp() != 1) {
            str = str + ' ';
        }
    }
    return str;
}

int eval(std::string pref) {
    std::string sP;
    char cP;
    for (char i : pref) {
        if ((i >= '0' && i <= '9')) {
            sP += i;
        } else if (!sP.empty() && i == ' ') {
            stack2.push(std::stoi(sP));
            sP.clear();
        } else {
            switch (i) {
                case '+' : {
                    cP = stack2.pop();
                    stack2.push(stack2.pop() + cP);
                    break;
                }
                case '*' : {
                    cP = stack2.pop();
                    stack2.push(stack2.pop() * cP);
                    break;
                }
                case '/': {
                    cP = stack2.pop();
                    stack2.push(stack2.pop() / cP);
                    break;
                }
                case '-' : {
                    cP = stack2.pop();
                    stack2.push(stack2.pop() - cP);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}
