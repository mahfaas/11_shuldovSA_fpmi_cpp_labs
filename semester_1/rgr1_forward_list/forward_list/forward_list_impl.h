#pragma once

#include <iterator>
#include <iostream>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>

class ForwardList {

private:
    struct Node {
        int32_t value_;
        Node* next_;

        explicit Node(int32_t value) : value_(value), next_(nullptr) {
        }
    };

public:
    class ForwardListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int32_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ForwardListIterator(Node* position) : position_(position) {
        }

        ForwardListIterator& operator++() {  // prefix
            if (position_ == nullptr) {
                throw std::out_of_range("ForwardListIterator: increment end()");
            }
            position_ = position_->next_;
            return *this;
        }

        ForwardListIterator operator++(int) {  // postfix
            ForwardListIterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(const ForwardListIterator& other) const {
            return (position_ == other.position_);
        }

        bool operator!=(const ForwardListIterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            if (position_ == nullptr) {
                throw std::out_of_range("ForwardListIterator: dereference end()");
            }
            return position_->value_;
        }

        pointer operator->() const {
            if (position_ == nullptr) {
                throw std::out_of_range("ForwardListIterator: access end()");
            }
            return &position_->value_;
        }

    private:
        Node* position_;
    };

    // methods for "ranged-based for loop"
    // 1) non-const version
    ForwardListIterator begin() {
        return ForwardListIterator(head_);
    }
    ForwardListIterator end() {
        return ForwardListIterator(nullptr);
    }

    // 2) const version
    // TODO: think about return type
    // (is it exactly ForwardListIterator?) тут надо написать свой ConstIterator тк сейчас поскольку
    // возвращается int32_t& мы можем менять даже константный список
    ForwardListIterator begin() const {
        return ForwardListIterator(head_);
    }
    ForwardListIterator end() const {
        return ForwardListIterator(nullptr);
    }

    // default constructor
    ForwardList() = default;

    // copy constructor
    ForwardList(const ForwardList& rhs);

    // Constructs a ForwardList with `count` copies of elements with value `value`.
    ForwardList(size_t count, int32_t value);

    // Constructs a ForwardList with std::initializer_list<int32_t>
    ForwardList(std::initializer_list<int32_t> init);

    // operator= overloading
    ForwardList& operator=(ForwardList rhs);

    // destructor
    ~ForwardList();

    // insert new element on the top of the list
    void PushFront(int32_t value);

    // delete first element of the list
    void PopFront();

    // remove every occurence of an element in the list
    // whose value equals to param `value`,
    // the remaining elements must remain in the same order
    void Remove(int32_t value);

    // erases all the elements
    void Clear();

    // find list's element by the `value`
    // returns true, if element exists
    // otherwise, returns false
    bool FindByValue(int32_t value);

    // print list's elements to stream separated by space
    void Print(std::ostream& out);

    // get first element of the list
    int32_t Front() const;

    // get size of the list
    size_t Size() const;

private:
    Node* head_ = nullptr;
    size_t size_ = 0;

    void swap(ForwardList& other) noexcept;
};