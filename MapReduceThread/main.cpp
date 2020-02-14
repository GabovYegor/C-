#include <thread>
#include <iostream>
#include <list>
#include <vector>

template <class Iter, class Func1, class Func2>
auto map_reduce(Iter p, Iter q, Func1 f1, Func2 f2, size_t threads) -> decltype(f2(f1(*p), f1(*p))) {
    using f1Val = decltype(f1(*p));
    std::vector <std::vector <f1Val>> resF1V;
    resF1V.reserve(threads);
    std::vector <std::thread> threadVec;

    for(unsigned i = 0; i < threads - 1; ++i) {
        Iter t = p;
        ++p;
        threadVec.emplace_back(std::thread([f1, &resF1V](Iter s, Iter e) {
                            std::vector<f1Val> f1res;
                            for (; s != e; ++s) {
                                f1res.emplace_back(f1(*s));
                            }
                            resF1V.emplace_back(f1res);
                        }, t, p));
    }

    threadVec.emplace_back(std::thread([f1, &resF1V](Iter s, Iter e) {
                        std::vector<f1Val> f1res;
                        for (; s != e; ++s) {
                            f1res.emplace_back(f1(*s));
                        }
                        resF1V.emplace_back(f1res);
                    }, p, q));

    for(auto& it: threadVec)
        it.join();

    std::vector<f1Val> resAfterF = resF1V[0];
    for(size_t i = 1; i < threadVec.size(); ++i) {
        std::vector<f1Val> temp = resF1V[i];
        resAfterF.insert(resAfterF.end(), temp.begin(), temp.end());
    }

    decltype(f2(f1(*p), f1(*p))) res = resAfterF[0];
    for(size_t i = 1; i < resAfterF.size(); ++i)
        res = f2(res, resAfterF[i]);

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
