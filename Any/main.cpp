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

    Any(const Any& other) : data_(other.data_->clone()) {}

    ~Any() { delete data_; }

    Any& operator= (const Any& other) {
        if(this != &other) {
            this->~Any();
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
    return 0;
}

