#include <boost/phoenix/phoenix.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

bool is_odd(int i) { return i % 2 == 1; }

int main()
{
  std::vector<int> v{1, 2, 3, 4, 5};

  std::cout << std::count_if(v.begin(), v.end(), is_odd) << '\n';
  
  std::cout << std::count_if(v.begin(), v.end(), [](int i){ return i % 2 == 1; }) << '\n';

  auto phoenix = boost::phoenix::placeholders::arg1 % 2 == 1;
  std::cout << std::count_if(v.begin(), v.end(), phoenix) << '\n';
}
