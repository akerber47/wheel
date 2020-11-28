#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

template <typename T> concept Ord =
  requires (T a, T b) { a < b; };

template <Ord T> void bubble_sort(std::vector<T> &a) {
  for (int i = a.size() - 1; i >= 1; --i) {
    for (int j = i; j >= 1; --j) {
      if (a[j] < a[j-1]) {
        int tmp = a[j];
        a[j] = a[j-1];
        a[j-1] = tmp;
      }
    }
  }
}

template <Ord T> void insertion_sort(std::vector<T> &a) {
  for (int i = 1; i < a.size(); ++i) {
    int tmp = a[i];
    int j;
    for (j = i-1; tmp < a[j] && j >= 0; --j) {
      a[j+1] = a[j];
    }
    a[j+1] = tmp;
  }
}

// Print helper
template <typename T> concept Printable =
  requires (T a) { std::cout << a; };

template <Printable T> void pv(const std::vector<T> &v) {
  std::cout << "[";
  for (auto x = v.begin(); x != v.end(); x++) {
    std::cout << *x;
    if (x+1 != v.end())
      std::cout << ",";
  }
  std::cout << "]";
}

void test_sort(
    void (*sort_func)(std::vector<int> &),
    const std::vector<int> &in,
    std::string name)
{
  auto exp = in, act = in;
  std::sort(exp.begin(), exp.end());
  sort_func(act);
  std::string res;
  if (exp == act) {
    res = "Passed! ";
  }
  else {
    res = "Failed! ";
  }
  std::cout << res << name << "(";
  pv<int>(in);
  std::cout << ")" << std::endl;

  if (exp != act) {
    std::cout << "  expected: ";
    pv<int>(exp);
    std::cout << std::endl;
    std::cout << "    actual: ";
    pv<int>(act);
    std::cout << std::endl;
  }
}


int main() {
  std::vector<int> v0 = {5};
  std::vector<int> v1 = {5, 1, 3, 4, 2};
  std::vector<int> v2 = {5, 1, 10, 3, 4, 2, 25, 5, 8};
  test_sort(bubble_sort<int>, v0, "bubble_sort");
  test_sort(bubble_sort<int>, v1, "bubble_sort");
  test_sort(bubble_sort<int>, v2, "bubble_sort");
  return 0;
}
