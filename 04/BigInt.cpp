#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "BigInt.h"

BigInt::BigInt() {}
BigInt::BigInt(int ss) {
    long long s = ss;
    if (s < 0) {
        sign = -1;
        s = -s;
    }
    number = new int[30]();
    set_number(s);
    resize();
}

BigInt my_sum(const BigInt &n1, const BigInt &n2) {
    BigInt tmp = 0, n_min, n_max;
    tmp.sign = n1.sign;
    tmp.lenth = n1.lenth + n2.lenth;
    tmp.number = new int[tmp.lenth]();
    int c = 0;
    for (int i = 0; i < std::min(n1.lenth, n2.lenth); i++) {
        tmp.number[i] = n1.number[i] + n2.number[i] + c;
        c = 0;
        if (tmp.number[i] > 9) {
            c = 1;
            tmp.number[i] %= 10;
        }
    }
    int res = n1.greater_num(n1, n2);
    if (res == -1) {
        n_max = n1;
        n_min = n2;
    } else {
        n_min = n1;
        n_max = n2;
    }
    for (int i = n_min.lenth; i < n_max.lenth; i++) {
        tmp.number[i] = n_max.number[i] + c;
        c = 0;
        if (tmp.number[i] > 9) {
            c = 1;
            tmp.number[i] %= 10;
        }
    }
    //std::cout << tmp << " " << n_max << " " << n_min << std::endl ;
    tmp.lenth = n_max.lenth;
    if (c == 1) {
        tmp.lenth++;
        tmp.number[n_max.lenth] = 1;
    }
    tmp.resize();
    return tmp;
}
BigInt BigInt::operator-(const BigInt &tmp1) const{//this-tmp
    BigInt ans = *this, tmp = tmp1;
    if (ans.sign != tmp.sign) {
        tmp.sign*=-1;
        return my_sum(ans, tmp);
    } else {
        return my_diff(ans, tmp);
    }
}
BigInt BigInt::operator+(const BigInt &tmp1) const{//ans+tmp
    BigInt ans = *this, tmp = tmp1;
    //std::cout << ans << " " << tmp << std::endl;
    if (ans.sign == tmp.sign)
        return my_sum(ans, tmp);
    else
    if (ans.sign == 1) {
        tmp.sign*=-1;
        return my_diff(ans, tmp);
    } else {
        ans.sign*=-1;
        return my_diff(tmp, ans);
    }
}
BigInt my_diff(const BigInt &n1, const BigInt &n2) {
    //std::cout << n1 << " ! " << n2 << std::endl;
    BigInt tmp = 0, n_min, n_max;
    int res = n1.greater_num(n1, n2);
    if (res == -1) {
        if (n1.sign == 1) {
            tmp.sign = 1;
        } else {
            tmp.sign = -1;
        }
        n_max = n1;
        n_min = n2;
    } else {
        if (n1.sign == 1) {
            tmp.sign = -1;
        } else {
            tmp.sign = 1;
        }
        n_max = n2;
        n_min = n1;
    }
    //std::cout << n_min << " ! " << n_max << std::endl;
    tmp.lenth = n1.lenth + n2.lenth;
    tmp.number = new int[tmp.lenth]();
    int c = 0;
    for (int i = 0; i < n_min.lenth; i++) {
        tmp.number[i] = n_max.number[i] - n_min.number[i] - c;
        c = 0;
        if (tmp.number[i] < 0) {
            c = 1;
            tmp.number[i] += 10;
        }
    }
    for (int i = n_min.lenth; i < n_max.lenth; i++) {
        tmp.number[i] = n_max.number[i] - c;
        c = 0;
        if (tmp.number[i] < 0) {
            c = 1;
            tmp.number[i] += 10;
        }
    }
    int cc = 0;
    for (int i = tmp.lenth - 1; i >= 0; i--) {
        if (tmp.number[i] == 0) {
            cc++;
        } else {
            break;
        }
    }
    tmp.lenth -= cc;
    if (tmp.lenth == 0) {
        tmp.lenth = 1;
    }
    tmp.resize();
    return tmp;
}
void BigInt::resize() {
    int* tmp = new int[this->lenth]();
    for (int i = 0; i < this->lenth; i++) {
        tmp[i] = number[i];
    }
    delete []number;
    number = tmp;
}
int BigInt::greater_num(const BigInt &n1, const BigInt &n2) const {
    if (n1.lenth > n2.lenth) {
        return -1;
    }
    if (n1.lenth < n2.lenth) {
        return 1;
    }
    for (int i = n1.lenth - 1; i >= 0; i--) {
        if (n1.number[i] > n2.number[i]) {
            return -1;
        }
        if (n1.number[i] < n2.number[i]) {
            return 1;
        }
    }
    return 0;
}
BigInt BigInt::operator-() {
    BigInt tmp = *this;
    tmp.sign *= -1;
    return tmp;
}
bool BigInt::operator>(const BigInt &num) const{
    if(this == &num) {
        return false;
    }
    if(this->sign * num.sign == 1) {
        return greater_num(*this, num) * this->sign < 0;
    } else {
        if(this->sign == 1) {
            return true;
        }
        return false;
    }
}

bool BigInt::operator<(const BigInt &num) const{
    if(this == &num) {
        return false;
    }
    if(this->sign * num.sign == 1) {
        return greater_num(*this, num) * this->sign > 0;
    } else {
        if(this->sign == -1) {
            return true;
        }
        return false;
    }
}

bool BigInt::operator<=(const BigInt &num) const{
    return !(*this > num);
}

bool BigInt::operator>=(const BigInt &num) const{
    return !(*this < num);
}
void BigInt::set_number(long long val) {
    lenth = 0;
    if (val == 0) {
        lenth = 1;
    } else {
        while (val != 0) {
            number[lenth] = (int)(val % 10);
            val /= 10;
            lenth++;
        }
    }
}
bool BigInt::operator==(const BigInt &num) const{
    if (this == &num) {
        return true;
    }
    if (greater_num(*this, num) == 0) {
        if (this->sign == num.sign) {
            return true;
        }
        if (this->lenth == 1 && this->number[0] == 0) {
            return true;
        }
    }
    return false;
}
bool BigInt::operator!=(const BigInt &num) const{
    return !(*this == num);
}
BigInt::~BigInt() {
    delete[] number;
}

BigInt::BigInt(const BigInt& val){
    //std::cout << val << " ! " << *this << std::endl;
    delete[]number;
    this->lenth = val.lenth;
    number = new int[this->lenth]();
    for (int i = 0; i < this->lenth; i++) {
        number[i] = val.number[i];
    }
    this->sign = val.sign;
    //std::cout << val << " ! " << *this << std::endl;
}
BigInt::BigInt(BigInt&& val){
    //delete[]number;
    //std::cout << val << " ! " << *this << std::endl;
    this->lenth = val.lenth;
    this->number = val.number;
    this->sign = val.sign;
    val.number = nullptr;
    val.lenth = 0;
    val.sign = 1;
    //std::cout << val << " ! " << *this << std::endl;
}

BigInt& BigInt::operator=(BigInt &&val)noexcept{
    delete[]number;
    this->lenth = val.lenth;
    this->number = val.number;
    this->sign = val.sign;
    val.number = nullptr;
    val.lenth = 0;
    val.sign = 1;
    return *this;
}
BigInt& BigInt::operator=(const BigInt &val){
    //std::cout << val << " ! " << *this << std::endl;
    delete[]number;
    this->lenth = val.lenth;
    number = new int[this->lenth]();
    for (int i = 0; i < this->lenth; i++) {
        number[i] = val.number[i];
    }
    this->sign = val.sign;
    //std::cout << val << " ! " << *this << std::endl;
    return *this;
}

BigInt& BigInt::operator=(int val){
    this->set_number(val);
    //BigInt tmp(val);
    //std::cout << val << " ! " << *this << std::endl;
    //*this = tmp;
    //std::cout << val << " ! " << *this << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream &ouput, const BigInt &tmp) {
    if (tmp.lenth != 0) {
        BigInt tmp1 = 0;
        if (tmp.sign < 0 && tmp.greater_num(tmp, tmp1)) {
            ouput << '-';
        }
        for (int i = tmp.lenth - 1; i >= 0; i--) {
            ouput << tmp.number[i];
        }
    }
    return ouput;
}

BigInt operator+(int tmp, const BigInt& tmp1) {
    return tmp1 + tmp;
}
BigInt operator-(int tmp, const BigInt& tmp1) {//3 - BigInt
    BigInt ans = tmp1 - tmp;
    ans.sign *= -1;
    return ans;
}

BigInt& BigInt::operator+=(const BigInt &tmp) {
    *this = *this + tmp;
    return *this;
}
BigInt& BigInt::operator-=(const BigInt &tmp) {
    *this = *this - tmp;
    return *this;
}

bool operator>(int t, const BigInt& t1){
    return t1 > t;
}
bool operator<=(int t, const BigInt& t1){
    return !(t1 > t);
}
bool operator<(int t, const BigInt& t1){
    return t1 < t;
}
bool operator>=(int t, const BigInt& t1){
    return !(t1 < t);
}
bool operator==(int t, const BigInt& t1){
    return t1 == t;
}
bool operator!=(int t, const BigInt& t1){
    return !(t1 == t);
}