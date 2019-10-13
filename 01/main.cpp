#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char op = '+';

bool is_sign(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    return false;
}

pair<int, bool> get_num (string &s) {
    int iter = 0;
    while(isspace(s[iter])) {
        iter++;
    }
    int tmp = 0, cnt = 0;
    bool num = false, sign = true;
    while (s[iter] == '-') {
        cnt++;
        iter++;
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
    int iter = 0;
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
                cerr << "ERROR : ZERO DIVISION" << endl;
                _Exit(1);
            }
            return a / b;
    }
}

int calculate (string &s, int mode = 0) {
    int ans = 0;
    switch (mode) {
        case 1: {
            ans = 1;
            char mul_op = '*';
            while (1) {
                pair<int, bool> res = get_num(s);
                if (res.second == 0) {
                    return ans;
                }
                char sign = get_sign(s);
                if (sign == '!') {
                    ans = make_op(ans, res.first, mul_op);
                    mul_op = sign;
                    return ans;
                } else {
                    ans = make_op(ans, res.first, mul_op);
                    mul_op = sign;
                }
                if (mul_op == '+' || mul_op == '-') {
                    op = mul_op;
                    return ans;
                }
            }
        }
        case 0: {
            while (1) {
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
                        ans = make_op(ans, calculate(s, 1), tmp_op);
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
            cerr << "ERROR : WRONG SYMBOLS" << endl;
            _Exit(1);
        }
    }
    pair<int, bool> tmp;
    char c;
    while (1) {
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
            cerr << "ERROR : NUMBER IS LOST" << endl;
            _Exit(1);
        } else {
            tmp = get_num(s);
            if (tmp.second == true) {
                cerr << "ERROR : SIGN IS LOST" << endl;
                _Exit(1);
            }
            c = get_sign(s);
            if (c != '!') {
                cerr << "ERROR : NUMBER IS LOST" << endl;
                _Exit(1);
            }
        }
    } else {
        tmp = get_num(s);
        if (tmp.second == true) {
            cerr << "ERROR : SIGN IS LOST" << endl;
            _Exit(1);
        }
        c = get_sign(s);
        if (c != '!') {
            cerr << "ERROR : NUMBER IS LOST" << endl;
            _Exit(1);
        }
    }
}
int main(int argc, char *argv[]) {
    string s = string(argv[1]);
    check_str(s);
    s = "0 + " + s;
    cout << to_string(calculate(s)) << endl;
    return 0;
}