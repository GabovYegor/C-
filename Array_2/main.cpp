#include <iostream>
#include <cstddef>
#include <string>
#include <cstring>

template <typename T>
class Array {
public:
    Array() : _data(nullptr), _size(0) {}

    explicit Array (size_t size, const T& value = 0)
        : _size(size), _data(static_cast<T*>(operator new [] (size * sizeof(T)))) {
        for(int i = 0; i < _size; ++i) {
            new (_data + i) T(value);
        }
    }

    Array(const Array & otherArray)
        : _size(otherArray._size),
          _data(static_cast<T*>(operator new [] (otherArray._size * sizeof(T)))) {

        for(int i = 0; i < _size; ++i)
            new (_data + i) T(otherArray._data[i]); // can`t use memcpy
    }

    Array& operator=(const Array& otherArray) {
        if(this != &otherArray) {
            this->~Array();
            _size = otherArray._size;
            _data = static_cast<T*>(operator new [] (otherArray._size * sizeof(T)));

            for(int i = 0; i < _size; ++i)
                new (_data + i) T(otherArray._data[i]); // can`t use memcpy
        }
        return *this;
    }

     ~Array() {
        for(int i =0 ; i < _size; ++i) {
            _data[i].~T();
        }
        operator delete[] (_data);
    }

     size_t size() const { return _size; }
     T& operator[](size_t index) { return _data[index]; }
     const T& operator[](size_t index) const { return _data[index]; }

private:
    T* _data;
    size_t _size;
};
