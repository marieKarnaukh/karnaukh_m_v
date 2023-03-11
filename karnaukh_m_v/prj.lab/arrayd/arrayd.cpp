#include <iostream>
#include <arrayd/arrayd.hpp>


ArrayD& ArrayD::operator=(ArrayD const& rhs) {
    if (this != &rhs) {
        delete[] data_;
        size_ = rhs.size_;
        data_ = new double[size_];
        for (int i = 0; i != size_; i += 1) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

double& ArrayD::operator[](ptrdiff_t ind) {  
    return *(data_ + ind);
}

const double ArrayD::operator[](ptrdiff_t ind) const {
    return *(data_ + ind);
}

ptrdiff_t ArrayD::size() const{
    return size_;
}

void ArrayD::resize(ptrdiff_t sizeNew) {
    double* dataNew = new double[sizeNew];
    ptrdiff_t n = size_ < sizeNew ? size_ : sizeNew;
    for (int i = 0; i < n; i += 1) {
        dataNew[i] = data_[i];
    }
    delete[] data_;
    data_ = dataNew;
    size_ = sizeNew;
}
