#include "forward_list_impl.h"

#include <utility>

ForwardList::ForwardList(size_t count, int32_t value) {

    Node* newHead = nullptr;
    Node* newTail = nullptr;
    size_t newSize = 0;

    try {
        for (size_t i = 0; i < count; ++i) {

            Node* fresh = new Node(value);

            if (newHead == nullptr) {
                newHead = fresh;
                newTail = fresh;
            } else {
                newTail->next_ = fresh;
                newTail = fresh;
            }
            ++newSize;
        }
    } catch (...) {
        while (newHead != nullptr) {
            Node* tmp = newHead;
            newHead = newHead->next_;
            delete tmp;
        }
        throw;
    }

    head_ = newHead;
    size_ = newSize;
}

ForwardList::ForwardList(const ForwardList& rhs) {

    Node* newHead = nullptr;
    Node* newTail = nullptr;
    size_t newSize = 0;

    try {
        for (Node* cur = rhs.head_; cur != nullptr; cur = cur->next_) {
            Node* fresh = new Node(cur->value_);

            if (newHead == nullptr) {
                newHead = fresh;
                newTail = fresh;
            } else {
                newTail->next_ = fresh;
                newTail = fresh;
            }

            ++newSize;
        }
    } catch (...) {
        while (newHead != nullptr) {
            Node* tmp = newHead;
            newHead = newHead->next_;
            delete tmp;
        }
        throw;
    }

    head_ = newHead;
    size_ = newSize;
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) {
    Node* newHead = nullptr;
    Node* newTail = nullptr;

    size_t newSize = 0;

    try {
        for (int32_t x : init) {
            Node* fresh = new Node(x);
            if (newHead == nullptr) {
                newHead = fresh;
                newTail = fresh;
            } else {
                newTail->next_ = fresh;
                newTail = fresh;
            }
            ++newSize;
        }
    } catch (...) {
        while (newHead != nullptr) {
            Node* tmp = newHead;
            newHead = newHead->next_;
            delete tmp;
        }
        throw;
    }
    head_ = newHead;
    size_ = newSize;
}

ForwardList& ForwardList::operator=(ForwardList rhs) {
    swap(rhs);
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::swap(ForwardList& other) noexcept {
    using std::swap;
    swap(head_, other.head_);
    swap(size_, other.size_);
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next_;
        delete tmp;
    }
    size_ = 0;
}

void ForwardList::PushFront(int32_t value) {
    Node* fresh = new Node(value);
    fresh->next_ = head_;
    head_ = fresh;
    ++size_;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        throw std::out_of_range("ForwardList::PopFront: list is empty");
    }
    Node* old = head_;
    head_ = head_->next_;
    delete old;
    --size_;
}

void ForwardList::Remove(int32_t value) {
    while (head_ != nullptr && head_->value_ == value) {
        Node* old = head_;
        head_ = head_->next_;
        delete old;
        --size_;
    }

    Node* cur = head_;
    while (cur != nullptr && cur->next_ != nullptr) {
        if (cur->next_->value_ == value) {
            Node* victim = cur->next_;
            cur->next_ = victim->next_;
            delete victim;
            --size_;
        } else {
            cur = cur->next_;
        }
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* cur = head_;
    while (cur != nullptr) {
        if (cur->value_ == value) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* cur = head_;
    while (cur != nullptr) {
        out << cur->value_;
        if (cur->next_ != nullptr) {
            out << ' ';
        }
        cur = cur->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        throw std::out_of_range("ForwardList::Front: list is empty");
    }
    return head_->value_;
}

size_t ForwardList::Size() const {
    return (size_);
}