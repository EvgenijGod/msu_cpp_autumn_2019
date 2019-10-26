#include <stdlib.h>
#include <iostream>
#include "Matrix.h"

Row::Row(int *matrix, size_t row, size_t row_len) {
    this->row_len = row_len;
    row_arr = matrix;
    row_arr += row * row_len;
}

int& Row::operator[](size_t iter) {
    if (iter >= this->row_len) {
        throw std::out_of_range("Error : column is out of range\n");
    }
    return row_arr[iter];
}

const int& Row::operator[](size_t iter) const{
    if (iter >= this->row_len) {
        throw std::out_of_range("Error : column is out of range\n");
    }
    return row_arr[iter];
}

Row::~Row() = default;
Matrix::Matrix() {};

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    matrix = (int *)calloc(rows * cols, sizeof(int));
    if (matrix == nullptr) {
        throw std::bad_alloc();
    }
}

size_t Matrix::getRows() {
    return rows;
}

size_t Matrix::getColumns() {
    return cols;
}

Matrix& Matrix::operator*=(size_t c){
    size_t n = rows * cols;
    for (int i = 0; i < n; i++) {
        matrix[i] *= c;
    }
    return *this;
}

bool Matrix::operator==(Matrix& m) const {
    if (this == &m) {
        return true;
    }
    if (m.rows != this->rows || m.cols != this->cols) {
        return false;
    }
    size_t n = rows * cols;
    for (int i = 0; i < n; i++) {
        if (this->matrix[i] != m.matrix[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix& m) const {
    return !(*this == m);
}

Row Matrix::operator[](size_t row) {
    if (row >= this->rows) {
        throw std::out_of_range("Error : row is out of range\n");
    }
    return Row(matrix, row, cols);
}

const Row Matrix::operator[](size_t row) const {
    if (row >= this->rows) {
        throw std::out_of_range("Error : row is out of range\n");
    }
    return Row(matrix, row, cols);
}

Matrix::~Matrix() {
    free(matrix);
}

