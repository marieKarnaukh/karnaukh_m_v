#include <iostream>
#include <cstdint>
#include <cmath>
#include <matrixs/matrixs.hpp>

MatrixS::MatrixS() : rows_(0), cols_(0), data_(0)
{}
MatrixS::MatrixS(const SizeType& size = {0, 0})
    : rows_(std::get<0>(size)), cols_(std::get<1>(size)) {
    if (rows_ < 0 || cols_ < 0) {
        throw std::invalid_argument("size cannot be negative");
    }
    data_ = new int[rows_ * cols_]{};
}
MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n)
    : rows_(m), cols_(n) {
    if (m < 0 || n < 0) {
        throw std::invalid_argument("size cannot be negative");
    }
    data_ = new int[rows_ * cols_]{};
}
MatrixS::MatrixS(const MatrixS& other) {
    if (this != &other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            delete[] data_;
            data_ = new int[other.rows_ * other.cols_]{};
        }
        rows_ = other.rows_;
        cols_ = other.cols_;
        std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    }
}
MatrixS::~MatrixS() {
    delete[] data_;
}
MatrixS& MatrixS::operator=(const MatrixS& other) {
    if (this != &other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            delete[] data_;
            data_ = new int[other.rows_ * other.cols_]{};
        }
        rows_ = other.rows_;
        cols_ = other.cols_;
        std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    }
    return *this;
}
int& MatrixS::at(const SizeType& elem) {
    if (std::get<0>(elem) < 0 ||
        std::get<1>(elem) < 0 ||
        std::get<0>(elem) >= rows_ ||
        std::get<1>(elem) >= cols_
       ) {
        throw std::out_of_range("out of range");
    }
    return *(data_ + std::get<0>(elem) * cols_ +  std::get<1>(elem));
}
const int& MatrixS::at(const SizeType& elem) const {
    if (std::get<0>(elem) < 0 ||
        std::get<1>(elem) < 0 ||
        std::get<0>(elem) >= rows_ ||
        std::get<1>(elem) >= cols_
       ) {
        throw std::out_of_range("out of range");
    }
    return *(data_ + std::get<0>(elem) * cols_ + std::get<1>(elem));
}

// method 'at' for writing a value with indexes
int& MatrixS::at(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (row < 0 ||
        col < 0 ||
        row >= rows_ ||
        col >= cols_
       ) {
        throw std::out_of_range("out of range");
    }
    return *(data_ + row * cols_ + col);
}

// same as method above for reading
const int& MatrixS::at(const std::ptrdiff_t row, const std::ptrdiff_t col) const {
    if (row < 0 ||
        col < 0 ||
        row >= rows_ ||
        col >= cols_
       ) {
        throw std::out_of_range("out of range");
    }
    return *(data_ + row * cols_ + col);
}

// method 'resize' for changing a size of matrix with tuple
void MatrixS::resize(const SizeType& new_size) {
    int row = std::get<0>(new_size);
    int col = std::get<1>(new_size);
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("size cannot be negative or zero");
    }
    if (row > rows_ || col > cols_) {
        int* pNewData = new int[row * col]{};
        std::copy(data_, data_ + rows_ * cols_, pNewData);
        delete[] data_;
        data_ = pNewData;
    }
    rows_ = row;
    cols_ = col;
}

// method 'resize' for changing a size of matrix with indexes
void MatrixS::resize(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("size cannot be negative or zero");
    }
    if (row > rows_ || col > cols_) {
        int* pNewData = new int[row * col]{};
        std::copy(data_, data_ + rows_ * cols_, pNewData);
        delete[] data_;
        data_ = pNewData;
    }
    rows_ = row;
    cols_ = col;
}
const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    return size_;
}
std::ptrdiff_t MatrixS::nRows() const noexcept {
    return rows_;
}
std::ptrdiff_t MatrixS::nCols() const noexcept {
    return cols_;
}
