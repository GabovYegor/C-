#include <iostream>

struct Expression {
    Expression() = default;
};
struct Number;
struct BinaryOperation;

struct SharedPtr {
    explicit SharedPtr(Expression *ptr = 0) {
        _ptr = ptr;
        if(_ptr) _refCounter = new int(1);
    }

    ~SharedPtr () {
        if(_ptr) --(*_refCounter);
        if(_ptr && !*_refCounter) {
            delete _refCounter;
            delete _ptr;
        }
    }

    SharedPtr(const SharedPtr& tempSharedPtr) :
        _ptr(tempSharedPtr._ptr),
        _refCounter(tempSharedPtr._refCounter) {

        if(_ptr) ++(*_refCounter);
    }

    SharedPtr& operator= (const SharedPtr& tempSharedPtr) {
        if(this == &tempSharedPtr) return *this;
        this->~SharedPtr();
        _ptr = tempSharedPtr._ptr;
        if(_ptr) {
            _refCounter = tempSharedPtr._refCounter;
            ++(*_refCounter);
        }
        return *this;
    }

    Expression* get() const {
        return _ptr;
    }

    void reset(Expression *ptr = 0) {
        if(_ptr) --(*_refCounter);
        if(_ptr && !*_refCounter) {
            delete _ptr;
            delete _refCounter;
        }
        _ptr = ptr;
        if(_ptr) _refCounter = new int(1);
    }

    Expression& operator*() const {
        return *_ptr;
    }

    Expression* operator->() const {
        return _ptr;
    }

private:
    int* _refCounter;
    Expression* _ptr;
};

int main() {
    SharedPtr p1;
    {
        SharedPtr p2(new Expression);
        SharedPtr p3(new Expression);
        SharedPtr p4(p2);
        SharedPtr p5;
        p5 = p2;
        p5 = p4;
        p1 = p5;
        p3.reset(nullptr);
        p3 = p5;
        p5.reset(nullptr);
        SharedPtr p6;
        SharedPtr p7;
        p7 = p7;
        p7.reset(nullptr);
        p7.reset(new Expression);
        SharedPtr p8(new Expression);
        p8.reset(nullptr);
    }
    p1 = p1;
    return 0;
}
