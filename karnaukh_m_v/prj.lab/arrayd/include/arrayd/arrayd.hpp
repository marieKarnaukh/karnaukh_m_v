#include <iosfwd>

class ArrayD {
public:
    ArrayD() = default;
    explicit ArrayD(ptrdiff_t sizeNew) //ctor
        : size_(sizeNew), capacity(2*sizeNew)
    {
        if (sizeNew < 0) {
            throw std::invalid_argument("Size should be positive");
        }
        data_ = new double[2 * sizeNew];
        for (int i = 0; i < capacity; i += 1) {
            data_[i] = 0.0;
        }
    }
    ArrayD(ArrayD const& a) //copy ctor
        : size_(a.size_), capacity(a.capacity)
    {
        data_ = new double[size_];
        for (int i = 0; i != size_; i += 1) { //std::copy вместо цикла
            data_[i] = a.data_[i];
        }
    }
    ~ArrayD() { //dctor
        delete[] data_;
    }

    ArrayD& operator=(ArrayD const& rhs);
    [[nodiscard]] double& operator[](ptrdiff_t ind);
    [[nodiscard]] const double operator[](ptrdiff_t ind) const;
    [[nodiscard]] ptrdiff_t ssize() const noexcept;
    void resize(ptrdiff_t sizeNew);
    void insert(const std::ptrdiff_t index, const double& value);
    void remove(const std::ptrdiff_t index);

private:
    ptrdiff_t size_{ 0 };
    ptrdiff_t capacity{ 0 };
    double* data_{ nullptr };

};

