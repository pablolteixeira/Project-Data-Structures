// "Copyright [2022[ <PABLO LOPES TEIXEIRA>"
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class ArrayList {
 public:
        ArrayList();
        explicit ArrayList(std::size_t max_size);
        ~ArrayList();
        void clear();
        void push_back(const T& data);
        void push_front(const T& data);
        void insert(const T& data, std::size_t index);
        void insert_sorted(const T& data);
        T pop(std::size_t index);
        T pop_back();
        T pop_front();
        void remove(const T& data);
        bool full() const;
        bool empty() const;
        bool contains(const T& data) const;
        std::size_t find(const T& data) const;
        std::size_t size() const;
        std::size_t max_size() const;
        T& at(std::size_t index);
        T& operator[](std::size_t index);
        const T& at(std::size_t index) const;
        const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;};
}  // namespace structures

#endif


template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("Array is full!");
    }
    contents[size_] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("Array is full!");
    }
    for (int i = size_; i > 0; i--) {
        contents[i] = contents[i-1];
    }
    contents[0] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full() || index >= max_size_) {
        throw std::out_of_range("Array is full/index is greater than max_size");
    }
    for (int i = size_; i > static_cast<int>(index); i--) {
        contents[i] = contents[i-1];
    }
    contents[index] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("Array is full/index is greater than max_size");
    }
    if (empty()) {
        contents[0] = data;
        size_++;
    } else {
        int tam = static_cast<int>(size_);
        for (int i = 0; i < static_cast<int>(size_); i++) {
            if (data < contents[i]) {
                for (int j = size_; j > i; j--) {
                    contents[j] = contents[j-1];
                }
                contents[i] = data;
                size_++;
                break;
            }
        }
        if (tam == static_cast<int>(size_)) {
            contents[size_] = data;
            size_++;
        }
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("Array is empty/indx is greater than max_size");
    }
    size_--;
    T temp = contents[index];
    for (int i = index; i < static_cast<int>(size_) - 1; i++) {
        contents[i] = contents[i+1];
    }
    return temp;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Array is empty!");
    }
    size_--;
    return contents[size_];
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Array is empty!");
    }
    T temp = contents[0];
    size_--;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        contents[i] = contents[i+1];
    }
    return temp;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (data == contents[i]) {
            for (int j = i; j < static_cast<int>(size_)-1; j++) {
                contents[j] = contents[j+1];
            }
            size_--;
            break;
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < static_cast<int>(size_) - 1; i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (contents[i] == data) {
            return static_cast<std::size_t>(i);
        }
    }
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index Error");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index Error");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

