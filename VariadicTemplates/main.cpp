#include <iostream>
#include <typeinfo>

void print_values(std::ostream&) { return; }

template <class T>
void print_values(std::ostream & os, T t) {
    os << typeid(t).name() << ": " << t << std::endl;
    return;
}

template <class T, class... Args>
void print_values(std::ostream & os, T t, Args... args) {
    os << typeid(t).name() << ": " << t << std::endl;
    print_values(os, args...);
    return;
}

int main() {
    print_values(std::cout);
    return 0;
}
