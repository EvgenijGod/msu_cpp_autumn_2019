#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

bool is_sign(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

pair<int, bool> get_num (string &s) {
    size_t iter = 0;
    while(isspace(s[iter])) {
        iter++;
    }
    int tmp = 0, cnt = 0;
    bool num = false, sign = true;
    while (s[iter] == '-') {
        cnt++;
        iter++;
        while(isspace(s[iter])) {
            iter++;
        }
    }
    if (cnt % 2 == 1) {
        sign = false;
    }
    while (isdigit(s[iter])) {
        tmp = tmp * 10 + int(s[iter] - '0');
        iter++;
        num = true;
    }
    if (num == true && sign == false) {
        tmp = -tmp;
    }
    s = s.substr((unsigned long long)iter);
    return make_pair(tmp, num);

}

char get_sign (string &s) {
    size_t iter = 0;
    while(isspace(s[iter])) {
        iter++;
    }
    char c = '!';
    if(is_sign(s[iter])) {
        c = s[iter];
        iter++;
    }
    s = s.substr((unsigned long long)iter);
    return c;

}

int make_op(int a, int b, char op1) {
    switch (op1) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                throw runtime_error("ZERO DIVISION");
            }
            return a / b;
    }
}

int calculate (string &s, char &op, int mode = 0) {
    //string s = s1;
    int ans = 0;
    switch (mode) {
        case 1: {
            ans = 1;
            char mul_op = '*';
            while (true) {
                pair<int, bool> res = get_num(s);
                if (res.second == 0) {
                    return ans;
                }
                char sign = get_sign(s);
                ans = make_op(ans, res.first, mul_op);
                mul_op = sign;
                if (sign == '!') {
                    return ans;
                }
                if (mul_op == '+' || mul_op == '-') {
                    op = mul_op;
                    return ans;
                }
            }
        }
        case 0: {
            while (true) {
                pair<int, bool> res = get_num(s);
                if (res.second == 0) {
                    return ans;
                }
                char sign = get_sign(s);
                if (sign == '!') {
                    ans = make_op(ans, res.first, op);
                    op = sign;
                    return ans;
                } else {
                    if (sign == '*' || sign == '/') {
                        char tmp_op = op;
                        s = to_string(res.first) + sign + s;
                        ans = make_op(ans, calculate(s, op, 1), tmp_op);
                    } else {
                        ans = make_op(ans, res.first, op);
                        op = sign;
                    }
                }
            }
        }
    }
    return ans;
}

void check_str(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (isspace(s[i]) || is_sign(s[i]) || isdigit(s[i])) {
            continue;
        } else {
            throw runtime_error(" WRONG SYMBOLS");
        }
    }
    pair<int, bool> tmp;
    char c;
    while (true) {
        tmp = get_num(s);
        if (tmp.second == false) {
            break;
        }
        c = get_sign(s);
        if (c == '!') {
            break;
        }
    }
    if (tmp.second == false) {
        if (c != '!') {
            throw runtime_error("NUMBER IS LOST");
        } else {
            tmp = get_num(s);
            if (tmp.second == true) {
                throw runtime_error("SIGN IS LOST");
            }
            c = get_sign(s);
            if (c != '!') {
                throw runtime_error("NUMBER IS LOST");
            }
        }
    } else {
        tmp = get_num(s);
        if (tmp.second == true) {
            throw runtime_error("SIGN IS LOST");
        }
        c = get_sign(s);
        if (c != '!') {
            throw runtime_error("NUMBER IS LOST");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        cerr << "ERROR : TOO MANY ARGUMENTS" << endl;
        _Exit(1);
    }
    if (argc == 1) {
        cerr << "ERROR : NO ARGUMENTS" << endl;
        _Exit(1);
    }
    string s = string(argv[1]);
    try {
        check_str(s);
    } catch (const exception &e) {
        cerr << "ERROR : " << e.what() << endl;
        return 1;
    }
    string exec = "0 + " + s;
    char op = '+';
    try {
        cout << to_string(calculate(exec, op)) << endl;
    } catch (const exception &e) {
        cerr << "ERROR : " << e.what() << endl;
        return 1;
    }
    return 0;
}