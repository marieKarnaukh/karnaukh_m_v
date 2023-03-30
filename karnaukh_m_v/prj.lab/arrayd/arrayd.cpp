#include <iostream>
#include <arrayd/arrayd.hpp>


ArrayD& ArrayD::operator=(ArrayD const& rhs) {
    if (this != &rhs) {
        if (rhs.size_ < size_)
        {
            for (ptrdiff_t i = 0; i < rhs.size_; i += 1) {
                data_[i] = rhs.data_[i];
            }
            for (ptrdiff_t i = rhs.size_; i < size_; i += 1) {
                data_[i] = 0.0;
            }
        }
        else if (rhs.size_ < capacity) {
            for (ptrdiff_t i = 0; i < rhs.size_; i += 1) {
                data_[i] = rhs.data_[i];
            }
        }
        else {
            delete[] data_;
            size_ = rhs.size_;
            capacity = 2 * rhs.size_;
            data_ = new double[2 * size_];
            for (int i = 0; i != size_; i += 1) {
                data_[i] = rhs.data_[i];
            }
        }
    }
    return *this;
}

double& ArrayD::operator[](ptrdiff_t ind) {
    if (ind >= size_ || ind < 0) {
        throw std::out_of_range("Out of range");
    }
    return *(data_ + ind);
}

const double ArrayD::operator[](ptrdiff_t ind) const {
    if (ind >= size_ || ind < 0) {
        throw std::out_of_range("Out of range");
    }
    return *(data_ + ind);
}

ptrdiff_t ArrayD::ssize() const noexcept{
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

void ArrayD::resize(ptrdiff_t sizeNew) {
    if (sizeNew <= 0) {
        throw std::invalid_argument("Size should be positive");
    }
    else {
        if (sizeNew > capacity) {

            double* dataNew = new double[2 * sizeNew];
            for (int i = 0; i < size_; i += 1) {
                dataNew[i] = data_[i];
            }
            delete[] data_;
            data_ = dataNew;
            capacity = 2 * size_;

        }
        if (sizeNew > size_ && sizeNew < capacity) {
            for (ptrdiff_t i = size_; i < sizeNew; i += 1) {
                data_[i] = 0.0;
            }
        }
        size_ = sizeNew;
    }
}

void ArrayD::insert(const std::ptrdiff_t index, const double& value) {
    if (size_ + 1 <= capacity) {
        size_ += 1;
    }
    else {
        resize(size_ + 1);
    }

    for (ptrdiff_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
}

void ArrayD::remove(const std::ptrdiff_t index) {
    if (index >= 0 && index < size_) {
        for (ptrdiff_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        size_ -= 1;
    }
    else {
        throw std::out_of_range("index out of range");
    }
}


