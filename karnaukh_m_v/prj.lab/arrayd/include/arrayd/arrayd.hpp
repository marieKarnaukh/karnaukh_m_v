#include <iosfwd>

class ArrayD {
public:
    ArrayD() = default;
    ArrayD(ptrdiff_t sizeNew) //ctor
        : size_(sizeNew), data_(new double[sizeNew])
    {}
    ArrayD(ArrayD const& a) //copy ctor
        : size_(a.size_), data_(new double[size_])
    {
        for (int i = 0; i != size_; i += 1) {
            data_[i] = a.data_[i];
        }
    }
    ~ArrayD() { //dctor
        delete[] data_;
    }

    ArrayD& operator=(ArrayD const& rhs);
    double& operator[](ptrdiff_t ind);
    const double operator[](ptrdiff_t ind) const;
    ptrdiff_t size() const ; //noexept
    void resize(ptrdiff_t sizeNew);

private:
    ptrdiff_t size_{ 0 };
    double* data_{ nullptr };

};

