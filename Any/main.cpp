#include <iostream>

struct ICloneable {
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() {}
};

class BaseHolder : public ICloneable {
public:
    virtual BaseHolder* clone() const override = 0;
    virtual ~BaseHolder() {}
};

template <typename T>
struct ValueHolder final : public BaseHolder {
    ValueHolder() = default;
    ValueHolder(const T& otherValue) : data_(otherValue) {}

    ValueHolder* clone() const override {
        return new ValueHolder(data_);
    }

    friend std::ostream& operator << (std::ostream& stream, const ValueHolder& data) {
        stream << data.data_ << std::endl;
        return stream;
    }

    ~ValueHolder() override {}
    T data_;
};

class Any {
public:
    Any() : data_(nullptr) {}

    template <class T>
    Any(T t) : data_(new ValueHolder<T>(t)) {}

    Any(const Any& other) {
        if(other.data_)
            data_ = other.data_->clone();
    }

    ~Any() { delete data_; }

    Any& operator= (const Any& other) {
        if(this != &other) {
            this->~Any();
            if(other.data_)
                data_ = other.data_->clone();
        }
        return *this;
    }

    template <class T>
    T* cast() {
        auto temp = dynamic_cast<ValueHolder<T>*> (data_);
        return temp ? &(temp->data_) : nullptr;
    }

    BaseHolder* data_;
};

int main() {
    std::string Hello = "Hello World People";
    ValueHolder<int> Int(10);
    ValueHolder<std::string> Str(Hello);
    double Dbl = 10.112233;
    int INT = 45;

    Any aHello(Hello);
    Any aInt(Int);
    Any aStr(Str);
    Any aDbl(Dbl);
    Any aINT(INT);

    std::cout << Hello.data() << std::endl;
    std::cout << aHello.cast<std::string>()->data() << std::endl;
    std::cout << aInt.cast<ValueHolder<int> >()->data_ << std::endl;
    std::cout << aStr.cast<ValueHolder<std::string> >()->data_.data() << std::endl;
    std::cout << *aDbl.cast<double>() << std::endl;
    std::cout << *aINT.cast<int>() << std::endl;

    aHello = (char*)"Any other simple text";
    aInt = 10241;
    aDbl = 234.5675;

    Any *pAny = new Any[5];
    for (int i = 0;i < 5;i++)
          pAny[i] = new Any(i*i + 1);

    std::cout << *aHello.cast<char *>() << std::endl;
    std::cout << *aInt.cast<int>() << std::endl;
    std::cout << *aDbl.cast<double>() << std::endl;

    std::cout << "Values of pAny:" << std::endl;
    for (int i = 0;i < 5;i++)
          std::cout << "\tpAny[" << i << "] = " << *(*pAny[i].cast<Any*>())->cast<int>() << std::endl;

    delete[] pAny;

    Any pAny2[30];

    for (int i = 0;i < 30;i++)
          pAny2[i] = Any(i + 1);

    std::cout << "Values of pAny2:" << std::endl;
    for (int i = 0;i < 30;i++)
          std::cout << "\tpAny2[" << i << "] = " << *pAny2[i].cast<int>() << std::endl;
    return 0;
}

