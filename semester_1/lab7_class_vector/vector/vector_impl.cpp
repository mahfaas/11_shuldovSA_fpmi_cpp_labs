#include "vector_impl.h"

#include <stdexcept>
#include <ostream>

Vector::Vector(size_t size) : data_(size ? new int[size] : nullptr), size_(size), capacity_(size) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<int> init)
    : data_(init.size() ? new int[init.size()] : nullptr),
      size_(init.size()),
      capacity_(init.size()) {
    std::size_t i = 0;
    for (int value : init) {
        data_[i++] = value;
    }
}

Vector::Vector(const Vector& other)
    : data_(other.capacity_ ? new int[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    if (other.capacity_ == 0) {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        return *this;
    }

    int* new_data = new int[other.capacity_];
    for (std::size_t i = 0; i < other.size_; ++i) {
        new_data[i] = other.data_[i];
    }

    delete[] data_;

    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept{
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

Vector::Vector(Vector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector::~Vector() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void Vector::Swap(Vector& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
}

int& Vector::operator[](std::size_t index) noexcept {
    return data_[index];
}

const int& Vector::operator[](std::size_t index) const noexcept {
    return data_[index];
}

int& Vector::At(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Vector::At: index out of range");
    }
    return data_[index];
}

const int& Vector::At(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Vector::At: index out of range");
    }
    return data_[index];
}

void Vector::PushBack(int value) {
    if (capacity_ == 0) {
        Reallocate_(1);
    } else if (size_ == capacity_) {
        Reallocate_(capacity_ * 2);
    }
    data_[size_] = value;
    ++size_;
}

void Vector::PopBack() noexcept {
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() noexcept {
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    Reallocate_(new_capacity);
}

void Vector::Reallocate_(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << '[';
    if (v.Size() > 0) {
        out << v[0];
        for (size_t i = 1; i < v.Size(); ++i) {
            out << ", " << v[i];
        }
    }
    out << ']';
    return out;
}