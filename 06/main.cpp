#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <assert.h>

using namespace std;

template <class T>
void process(vector<string>&res, T&& val)
{
    stringstream tmp;
    tmp << val;
    res.push_back(tmp.str());
}

template <class T, class... Args>
void process(vector<string>&res, T&& val, Args&&... args)
{
    stringstream tmp;
    tmp << val;
    res.push_back(tmp.str());
    process(res, forward<Args>(args)...);
}

template <class... Args>
string format(string str, Args&&... args) {
    vector<string>res;
    stringstream out;
    process(res, forward<Args>(args)...);
    bool open = false;
    int n = str.size();
    for (int i = 0; i < n; i++) {
        if (str[i] == '{') {
            int num = 0;
            i++;
            while(i < n && str[i] != '}') {
                if (isdigit(str[i]) == false) {
                    throw runtime_error("out of context");
                }
                num = num * 10 + (int)(str[i] - '0');
                i++;
            }
            if (i == n || num >= res.size()) {
                throw runtime_error("out of context");
            }
            out << res[num];
        } else {
            out << str[i];
        }
    }
    return out.str();
}

int main() {
    string ans;
    try {
        auto text = format("{1}+{1} = {0}", 2, "one");
        ans = text;
    } catch (const exception &e){
        cout << e.what() << endl;
    }
    assert(ans == "one+one = 2");
    try {
        auto text = format("{1}+{2}{2}:){0} = {0}", 2, "one", -333);
        ans = text;
    } catch (const exception &e){
        cout << e.what() << endl;
    }
    assert(ans == "one+-333-333:)2 = 2");
    try {
        auto text = format("{1}+{1} = {-jduduge}", 2, "one");
        ans = text;
    } catch (const exception &e){
        cout << e.what() << endl;
    }
    assert(ans == "one+-333-333:)2 = 2");
    cout << "OK";
    return 0;
}