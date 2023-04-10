#include <iostream>

class ArrayD {
public:
    ArrayD();
    explicit ArrayD(const std::ptrdiff_t sizeNew);
    ArrayD(const ArrayD& a);
    ~ArrayD() { //dctor
        delete[] data_;
    }

    ArrayD& operator=(const ArrayD& rhs);
    [[nodiscard]] double& operator[](std::ptrdiff_t ind);
    [[nodiscard]] const double operator[](std::ptrdiff_t ind) const;
    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;
    void resize(std::ptrdiff_t sizeNew);
    void insert(const std::ptrdiff_t index, const double& value);
    void remove(const std::ptrdiff_t index);

private:
    std::ptrdiff_t size_{ 0 };
    std::ptrdiff_t capacity{ 0 };
    double* data_{ nullptr };

};

