#ifndef SPHERE_MATRIX_H
#define SPHERE_MATRIX_H

class Row {
    int *row_arr = nullptr;
    size_t row_len = 0;
public:
    Row(int *matrix, size_t row, size_t row_len);
    int& operator[](size_t iter) const ;
    ~Row();
};


class Matrix {
private:
    int *matrix = nullptr;
    size_t rows = 0;
    size_t cols = 0;
public:
    Matrix(size_t rows, size_t cols);
    size_t getRows() ;
    size_t getColumns() ;
    const Matrix& operator*=(size_t c) const;
    bool operator==(const Matrix& m) const ;
    bool operator!=(const Matrix& m) const ;
    const Row operator[](size_t row) const ;
    ~Matrix();
};

#endif //SPHERE_MATRIX_H
