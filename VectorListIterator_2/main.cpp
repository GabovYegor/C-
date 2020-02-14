#include <iostream>
#include <iterator>
#include <vector>
#include <list>

template<class T>
class VectorList {
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    template<class It>
    void append(It p, It q) {
        if (p != q)
            data_.push_back(VectT(p,q));
    }

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const {
        size_t size = 0;
        for(auto it: data_) {
            size += it.size();
        }
        return size;
    }

    class const_iterator : public std::iterator <std::bidirectional_iterator_tag, value_type> {
    public:
        using lcIt = typename ListT::const_iterator;
        using vcIt = typename VectT::const_iterator;
        using value = T;
        value_type* data_;
        lcIt listIt_;
        vcIt vecIt_;

        const_iterator () = default;
        const_iterator (const const_iterator&) = default;
        const_iterator (lcIt listIt, vcIt vecIt) :
            listIt_(listIt), vecIt_(vecIt) {
            data_ = const_cast<value_type*> (&*vecIt_);
        }

        const_iterator& operator-- () {
            if(listIt_->begin() == vecIt_) {
                --listIt_;
                vecIt_ = listIt_->end();
            }
            data_ = const_cast<value_type*> (&*--vecIt_);
            return *this;
        }

        const_iterator& operator++ () {
            if(--listIt_->end() == vecIt_) {
                ++listIt_;
                vecIt_ = listIt_->begin();
                data_ = const_cast<value_type*> (&*vecIt_);
                return *this;
            }
            data_ = const_cast<value_type*> (&*++vecIt_);
            return *this;
        }

        value_type& operator* () const { return *data_; }
        value_type* operator->() const { return  data_; }
        const_iterator& operator-- (int) { return --*this; }
        const_iterator& operator++ (int) { return ++*this; }
        bool operator == (const const_iterator cIt) { return cIt.data_ == data_ ? true : false; }
        bool operator !=(const const_iterator cIt) { return !(*this == cIt); }
    };

    const_iterator begin() const { return const_iterator(data_.begin(), data_.begin()->begin()); }
    const_iterator end() const { return const_iterator(--data_.end(), (--data_.end())->end()); }

private:
    ListT data_;
};


int main() {
    VectorList<int> vlist;
    std::vector<int> v1 = {45,1,2,3};
    std::vector<int> v2 = {4,5,6,79};
    vlist.append(v1.begin(), v1.end());
    vlist.append(v2.begin(), v2.end());
    return 0;
}
