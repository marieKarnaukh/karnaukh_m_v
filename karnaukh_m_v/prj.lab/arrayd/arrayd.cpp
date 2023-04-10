#include <iostream>
#include <arrayd/arrayd.hpp>

ArrayD::ArrayD()
    : size_(0), capacity(0), data_(nullptr)
{}

ArrayD::ArrayD(const std::ptrdiff_t sizeNew) { //ctor
    if (sizeNew < 0) {
        throw std::invalid_argument("Size should be positive");
    } else if (sizeNew == 0) {
        size_ = 0;
        capacity = 0;
        data_ = nullptr;
    }
    size_ = sizeNew;
    capacity = sizeNew * 2;
    data_ = new double[2 * sizeNew]{}; // fills with default value
}

ArrayD::ArrayD(ArrayD const& a) //copy ctor
    : size_(a.size_), capacity(a.capacity) {
    data_ = new double[capacity]{};
    for (int i = 0; i < size_; i += 1) { // std::copy ������ �����
        data_[i] = a.data_[i];
    }
}

ArrayD& ArrayD::operator=(ArrayD const& rhs) {
    if (this != &rhs) {
        delete [] data_;
        size_ = rhs.size_;
        capacity = rhs.size_ * 2;
        data_ = new double[capacity]{};
        for(int i = 0; i < rhs.size_; i += 1) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

double& ArrayD::operator[](std::ptrdiff_t ind) {
    if (ind >= size_ || ind < 0) {
        throw std::out_of_range("Out of range");
    }
    return *(data_ + ind);
}

const double ArrayD::operator[](std::ptrdiff_t ind) const {
    if (ind >= size_ || ind < 0) {
        throw std::out_of_range("Out of range");
    }
    return *(data_ + ind);
}

std::ptrdiff_t ArrayD::ssize() const noexcept{
    return size_;
}

/*void ArrayD::resize(ptrdiff_t sizeNew) {
    double* dataNew = new double[sizeNew];
    ptrdiff_t n = size_ < sizeNew ? size_ : sizeNew;
    for (int i = 0; i < n; i += 1) {
        dataNew[i] = data_[i];
    }
    delete[] data_;
    data_ = dataNew;
    size_ = sizeNew;
}*/
/*double* pointer = data_ + size_;
 pointer = new double[sizeNew - size_];
 realSize = sizeNew;
 */

//std::fill

void ArrayD::resize(std::ptrdiff_t sizeNew) {
    if (sizeNew <= 0) {
        throw std::invalid_argument("size cannot be negative or null");
    }
    if (sizeNew > capacity) {
        capacity = sizeNew * 2;
        double *pNewData = new double[capacity]{};
        for (std::ptrdiff_t i = 0; i < this->size_; ++i) {
            pNewData[i] = data_[i];
        }
        for (std::ptrdiff_t i = this->size_; i < sizeNew; ++i) {
            pNewData[i] = 0;
        }
        delete [] data_;
        data_ = pNewData;
    }
    size_ = sizeNew;
}

void ArrayD::insert(const std::ptrdiff_t index, const double& value) {
    if (index >= size_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    if (size_ + 1 <= capacity) {
        size_ += 1;
    }
    else {
        resize(size_ + 1);
    }
    for (std::ptrdiff_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
}

void ArrayD::remove(const std::ptrdiff_t index) {
    if (index >= 0 && index < size_) {
        for (std::ptrdiff_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        size_ -= 1;
    }
    else {
        throw std::out_of_range("index out of range");
    }
}


