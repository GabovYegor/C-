#include <iostream>

template <class T, class V>
class SameType {
public:
    static const bool value = false;
};

template <class T>
class SameType <T, T> {
public:
    static const bool value = true;
};

int main() {
    std::cout << SameType<const int, const int>::value << std::endl;
    return 0;
}
