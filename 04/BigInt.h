#ifndef SPHERE_MATRIX_H
#define SPHERE_MATRIX_H

#include <iostream>
class BigInt {
private:
    int *number = nullptr;
    int sign = 1;
    int lenth = 0;
    int greater_num(const BigInt &n1, const BigInt &n2) const;
    void resize();

public:
    BigInt();
    BigInt(int s);
    BigInt(const BigInt& tmp);
    BigInt(BigInt&& tmp);
    BigInt operator-();
    BigInt& operator=(BigInt &&val)noexcept;
    BigInt& operator=(const BigInt &val);
    BigInt& operator=(int val);
    bool operator>(const BigInt &num) const;
    bool operator>=(const BigInt &num) const;
    bool operator<(const BigInt &num) const;
    bool operator<=(const BigInt &num) const;
    bool operator==(const BigInt &num) const;
    bool operator!=(const BigInt &num) const;
    BigInt operator+(const BigInt &tmp) const;
    BigInt operator-(const BigInt &tmp) const;
    BigInt& operator+=(const BigInt &tmp);
    BigInt& operator-=(const BigInt &tmp);
    friend std::ostream& operator<<(std::ostream &output, const BigInt &tmp);
    ~BigInt();
    friend BigInt my_sum(const BigInt &n1, const BigInt &n2);
    friend BigInt my_diff(const BigInt &n1, const BigInt &n2);
    friend BigInt operator+(int t, const BigInt& t1);
    friend BigInt operator-(int t, const BigInt& t1);

};
bool operator>(int t, const BigInt& t1);
bool operator<(int t, const BigInt& t1);
bool operator>=(int t, const BigInt& t1);
bool operator<=(int t, const BigInt& t1);
bool operator!=(int t, const BigInt& t1);
bool operator==(int t, const BigInt& t1);
#endif //SPHERE_MATRIX_H
