#include <iostream>
#include <cstddef>
#include <algorithm>

using namespace std;

template <typename T>
class Array {
public:
    explicit Array(size_t size = 0, const T& value = T()) :
        _size(size), _data(new T[size]) {

        std::fill(_data, _data + _size, value);
    }

    Array(const Array& tempArray) :
        _size(tempArray._size), _data(new T[tempArray._size]){

        for(size_t i = 0; i < _size; ++i) {
            _data[i] = tempArray._data[i];
        }
    }

    ~Array() {
        delete[] _data;
    }

    Array& operator= (const Array& tempArray) {
        if(this == &tempArray) return *this;
        this->~Array();
        _size = tempArray._size;
        _data = new T[tempArray._size];
        for(size_t i = 0; i < _size; ++i) {
            _data[i] = tempArray._data[i];
        }
        return *this;
    }

    size_t size() const {
        return _size;
    }

    T& operator[](size_t index) {
        return _data[index];
    }

    const T& operator[](size_t index) const {
        return _data[index];
    }

    void print() const {
        for(size_t i = 0; i < _size; ++i) {
            cout << _data[i];
        }
    }

private:
    T* _data;
    size_t _size;
};

void test0()
{
    {
        cout << endl << "*****Test 0**********" << endl;
        cout << endl << "*****CHAR**********" << endl;
        Array<char> ar(size_t(5), '0');
        Array<char> x(size_t(4), '4');
        ar = x;
        ar.print();

        Array<char> x2(size_t(6), '6');
        ar = x2;
        ar.print();
    }
    {
        cout << endl << "*****STRING**********" << endl;
        Array<string> cr(size_t(5), "0");
        Array<string> cx(size_t(4), "4");
        cr = cx;
        cr.print();

        Array<string> cx2(size_t(6), "6");
        cr = cx2;
        cr.print();
    }
    {
        cout << endl << "*****INT**********" << endl;
        Array<int> ir(size_t(5), 0);
        Array<int> ix(size_t(4), 4);
        ir = ix;
        ir.print();

        Array<int> ix2(size_t(6), 6);
        ir = ix2;
        ir.print();
    }

    {
        cout << endl << "*****DOUBLE**********" << endl;
        Array<double> dr(size_t(5), 0.0);
        Array<double> dx(size_t(4), 4.0);
        dr = dx;
        dx.print();

        Array<double> ix2(size_t(6), 6.0);
        dr = ix2;
        dr.print();
    }
    return;
}


void test1()
{
    {
        cout << endl << "*****Test 1(assigment)**********" << endl;
        Array<char> ar(size_t(100), '0');
        Array<char> x(size_t(0), '1');
        ar = x;
        ar.print();
    }
    {
        cout <<  "*****STRING**********" << endl;
        Array<string> cr(size_t(100), "0");
        Array<string> cx(size_t(0), "1");
        cr = cx;
        cr.print();

        Array<string> cx2(size_t(2), "55");
        cr = cx2;
        cr.print();
    }
    {
        cout << "*****INT**********" << endl;
        Array<int> cr(size_t(100), 0);
        Array<int> cx(size_t(0), 15);
        cr = cx;
        cr.print();

        Array<int> cx2(size_t(2), 55);
        cr = cx2;
        cr.print();
    }
    return;
}
void test2()
{
    cout << endl << "*****Test 2(copy constructor)**********" << endl;
    {
        cout << "*****CHAR**********" << endl;
        Array<char> x(size_t(3), '3');
        Array<char> ar(x);
        ar.print();
    }
    {
        cout << "*****STRING**********" << endl;
        Array<string> x(size_t(3), "333");
        Array<string> ar(x);
        ar.print();
    }

    return;
}

void test3()
{
    cout << endl << "*****Test 3(Empty)**********" << endl;
    {
        cout << "*****CHAR**********" << endl;
        Array<char> ar(size_t(0), '0');
        ar = ar;
        ar.print();
    }
    {
        cout << "*****STRING**********" << endl;
        Array<string> ar(size_t(0), "0");
        ar = ar;
        ar.print();
    }
    return;
}

void test4()
{
    cout << endl << "*****Test 4(assigment A=A) **********" << endl;
    {
        Array<char> ar(size_t(4), '0');
        ar = ar;
        ar.print();
    }
    return;
}
void test5()
{
    cout << endl << "*****Test 5(out bound)**********" << endl;
    {
        cout << "*****more**********" << endl;
        Array<char> ar(size_t(4), '0');
        cout << ar[10] << endl;
    }
    {
        cout << "*****less**********" << endl;
        Array<char> ar(size_t(4), '0');
        cout << ar[-10] << endl;
    }
    return;
}

void test6()
{
    cout << endl << "*****Test 6(pointer)**********" << endl;
    {
        Array<char> *ar = new Array<char>(size_t(4), '4');
        ar->print();
        delete ar;
    }
    {
        Array<char> *ar = new Array<char>(size_t(5), '5');
        ar->print();
        Array<char> *xr = ar;
        xr->print();
        delete ar;
    }
    return;
}

int main() {
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}
