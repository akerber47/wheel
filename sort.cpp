#include <vector>
#include <string>
#include <iostream>
#include <cassert>

void bubble_sort(std::vector<int> a) {
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

void insertion_sort(std::vector<int> a) {
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
template <typename T> void pv(const std::vector<T> &v) {
  std::cout << "[";
  for (auto x = v.begin(); x != v.end(); x++) {
    std::cout << *x;
    if (x+1 != v.end())
      std::cout << ",";
  }
  std::cout << "]" << std::endl;
}

int main() {
  std::vector<int> v0 = {5};
  std::vector<int> v1 = {5, 1, 3, 4, 2};
  std::vector<int> v2 = {5, 1, 10, 3, 4, 2, 25, 5, 8};
  auto v0_1 = v0;
  assert(v0_1 == v0);
  pv<int>(v0);
  pv<int>(v1);
  pv<int>(v2);
  return 0;
}
