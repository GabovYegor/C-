#include <future>
#include <iostream>
#include <functional>
#include <list>
#include <vector>

template <class Iter, class Func1, class Func2>
auto map_reduce(Iter p, Iter q, Func1 f1, Func2 f2, size_t threads) -> decltype(f2(f1(*p), f1(*p))) {
    using f1Val = decltype(f1(*p));

    auto distance = std::distance(p, q);
    auto group_size = (distance + threads - 1) / threads;
    std::vector <std::future <std::vector<f1Val>>> fV;
    for(unsigned i = 0; i < threads - 1; ++i) {
        Iter t = p;
        ++p;
        fV.emplace_back(std::async(std::launch::async, [f1](Iter s, Iter e) -> std::vector<f1Val> {
                            std::vector<f1Val> f1res;
                            for (; s != e; ++s) {
                                f1res.emplace_back(f1(*s));
                            }
                            return f1res;
                        }, t, p));
    }

    fV.emplace_back(std::async(std::launch::async, [f1](Iter s, Iter e) -> std::vector<f1Val> {
                        std::vector<f1Val> f1res;
                        for (; s != e; ++s) {
                            f1res.emplace_back(f1(*s));
                        }
                        return f1res;
                    }, p, q));

    std::vector<f1Val> resF1 = fV[0].get();
    for(size_t i = 1; i < fV.size(); ++i) {
        std::vector<f1Val> temp = fV[i].get();
        resF1.insert(resF1.end(), temp.begin(), temp.end());
    }

    decltype(f2(f1(*p), f1(*p))) res = resF1[0];
    for(size_t i = 1; i < resF1.size(); ++i)
        res = f2(res, resF1[i]);

    return res;
}


int main() {
    std::list<int> l = {1,3,5,6,7,9};
    auto sum = map_reduce(l.begin(), l.end(),
                          [](int i){return i;},
    std::plus<int>(), 4);
    std::cout << sum << std::endl;

    auto has_even = map_reduce(l.begin(), l.end(),
                               [](int i){return i % 2 == 0;},
    std::logical_or<bool>(), 1);
    std::cout << has_even << std::endl;
    return 0;
}
