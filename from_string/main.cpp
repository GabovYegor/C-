#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <exception>

// описание класса исключения bad_from_string
class bad_from_string : public std::exception {
public:
    bad_from_string(std::string str) : str_(str) {}
    virtual const char* what() noexcept { return str_.c_str(); }
private:
    std::string str_;
};

// функция from_string
template<class T>
T from_string(std::string const& s) {
    std::istringstream ss (s);
    T result;
    ss >> std::noskipws >> result;
    if(ss.fail() || ss.peek() != EOF)
        throw bad_from_string("EOF ERROR. ARGUMENT: " + s + " Type: " + typeid(T).name());
    return result;
}

int main() {
    std::string s1("123");
    from_string<int>   (s1); // a1 = 123
    from_string<double>(s1); // b1 = 123.0
    from_string<std::string>(s1); // c1 = "123"

    std::string s2("12.3");
    from_string<int>   (s2); // исключение
    from_string<double>(s2); // b2 = 12.3
    from_string<std::string>(s2); // c2 = "12.3"

    std::string s3("abc");
    from_string<int>   (s3); // исключение
    from_string<double>(s3); // исключение
    from_string<std::string>(s3); // c3 = "abc"
    from_string<char>("r");
    from_string<char>("e"); // пробел
    from_string<char>(""); // пробел
    from_string<char>("  "); // пробел
    from_string<char>(" d"); // пробел

    return 0;
}
