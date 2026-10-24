#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class ArrayList {
public:
    explicit ArrayList(std::size_t min_size = 1)
        : min_size_(min_size == 0 ? 1 : min_size),
          capacity_(min_size_),
          size_(0),
          data_(new T[capacity_]) {}

    ArrayList(const ArrayList& other)
        : min_size_(other.min_size_),
          capacity_(other.capacity_),
          size_(other.size_),
          data_(new T[other.capacity_]) {
        for (std::size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    ArrayList(ArrayList&& other) noexcept
        : min_size_(other.min_size_),
          capacity_(other.capacity_),
          size_(other.size_),
          data_(other.data_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ArrayList& operator=(ArrayList other) noexcept {
        std::swap(min_size_, other.min_size_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
        return *this;
    }

    ~ArrayList() { delete[] data_; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    T& operator[](std::size_t i) { return data_[i]; }
    const T& operator[](std::size_t i) const { return data_[i]; }

    T& at(std::size_t i) {
        check_index(i);
        return data_[i];
    }
    const T& at(std::size_t i) const {
        check_index(i);
        return data_[i];
    }

    void push_back(const T& value) {
        grow_if_full();
        data_[size_++] = value;
    }

    void insert(std::size_t pos, const T& value) {
        if (pos > size_) throw std::out_of_range("ArrayList::insert");
        grow_if_full();
        for (std::size_t i = size_; i > pos; --i) data_[i] = std::move(data_[i - 1]);
        data_[pos] = value;
        ++size_;
    }

    void erase(std::size_t pos) {
        check_index(pos);
        for (std::size_t i = pos; i + 1 < size_; ++i) data_[i] = std::move(data_[i + 1]);
        --size_;
        shrink_if_sparse();
    }

    void pop_back() {
        if (size_ == 0) throw std::out_of_range("ArrayList::pop_back");
        erase(size_ - 1);
    }

    void clear() {
        size_ = 0;
        if (capacity_ != min_size_) resize(min_size_);
    }

private:
    std::size_t min_size_;
    std::size_t capacity_;
    std::size_t size_;
    T* data_;

    void check_index(std::size_t i) const {
        if (i >= size_) throw std::out_of_range("ArrayList: index out of range");
    }

    void resize(std::size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void grow_if_full() {
        if (size_ == capacity_) resize(capacity_ * 2);
    }

    void shrink_if_sparse() {
        if (capacity_ > min_size_ && size_ <= capacity_ / 4) {
            std::size_t half = capacity_ / 2;
            resize(half < min_size_ ? min_size_ : half);
        }
    }
};

#endif