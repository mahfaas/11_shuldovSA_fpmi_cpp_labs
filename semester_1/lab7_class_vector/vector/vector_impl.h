#pragma once

#include <iosfwd>
#include <cstddef>
#include <initializer_list>

class Vector {
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void Reallocate_(size_t new_capacity);

public:
    Vector() = default;
    explicit Vector(size_t size);
    Vector(std::initializer_list<int> init);

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector& operator=(Vector&& other) noexcept;
    Vector(Vector&& other) noexcept;
    
    ~Vector();

    void Swap(Vector& other) noexcept;

    int& operator[](size_t index) noexcept;
    const int& operator[](size_t index) const noexcept;

    int& At(size_t index);
    const int& At(size_t index) const;

    size_t Size() const noexcept { return size_; }
    size_t Capacity() const noexcept { return capacity_; }

    void PushBack(int value);
    void PopBack() noexcept;

    void Clear() noexcept;

    void Reserve(size_t new_capacity);

};

std::ostream& operator<<(std::ostream& out, const Vector& v);
