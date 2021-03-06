#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "common.h"

template <Ord T> void bubble_sort(std::vector<T> &a) {
  for (int i = 0; i < a.size(); ++i) {
    for (int j = a.size() - 1; j > i; --j) {
      if (a[j] < a[j-1]) {
        T tmp = a[j];
        a[j] = a[j-1];
        a[j-1] = tmp;
      }
    }
  }
}

template <Ord T> void insertion_sort(std::vector<T> &a) {
  for (int i = 1; i < a.size(); ++i) {
    T tmp = a[i];
    int j;
    for (j = i-1; tmp < a[j] && j >= 0; --j) {
      a[j+1] = a[j];
    }
    a[j+1] = tmp;
  }
}

template <Ord T> void heap_sort(std::vector<T> &a) {
  // build max heap (largest at top)
  for (int i = 1; i < a.size(); ++i) {
    bool done = false;
    for (int j = i; !done && j > 0; ) {
      int pj = (j - 1) / 2;
      if (a[pj] < a[j]) {
        T tmp = a[j];
        a[j] = a[pj];
        a[pj] = tmp;
        j = pj;
      } else {
        done = true;
      }
    }
  }

  // extract from heap
  for (int i = a.size() - 1; i > 0; --i) {
    T tmp = a[i];
    a[i] = a[0];
    a[0] = tmp;
    bool done = false;
    for (int j = 0; !done && j < i; ) {
      int jl = j * 2 + 1, jr = j * 2 + 2;
      if (jr < i && a[j] < a[jr] && a[jl] < a[jr]) {
        T tmp = a[j];
        a[j] = a[jr];
        a[jr] = tmp;
        j = jr;
      } else if (jl < i && a[j] < a[jl]) {
        T tmp = a[j];
        a[j] = a[jl];
        a[jl] = tmp;
        j = jl;
      } else {
        done = true;
      }
    }
  }
}

template <Ord T> void merge_sort_helper(
    std::vector<T> &v,
    int start,
    int end) {
  if (end - start <= 1) {
    return;
  }
  int mid = (start + end) / 2;
  merge_sort_helper(v, start, mid);
  merge_sort_helper(v, mid, end);
  std::vector<T> out;
  int i1, i2;
  for (i1 = start, i2 = mid; i1 < mid && i2 < end; ) {
    if (v[i1] < v[i2]) {
      out.push_back(v[i1]);
      ++i1;
    } else {
      out.push_back(v[i2]);
      ++i2;
    }
  }
  for (; i1 < mid; i1++) {
    out.push_back(v[i1]);
  }
  for (; i2 < end; i2++) {
    out.push_back(v[i2]);
  }

  for (int i = 0; i < end - start; i++) {
    v[start + i] = out[i];
  }
}

template <Ord T> void merge_sort(std::vector<T> &a) {
  merge_sort_helper(a, 0, a.size());
}

template <Ord T> void quick_sort_helper(
    std::vector<T> &v,
    int start,
    int end) {
  // std::cout << "qs: start = " << start << ", end = " << end << std::endl;
  if (end - start <= 1) {
    return;
  }
  int pivot = start;
  int i, j;
  for (i = start + 1, j = end - 1; i < j; ) {
    // std::cout << "qs: loop i = " << i << ", j = " << j << std::endl;
    if (v[j] < v[pivot] && v[pivot] < v[i]) {
      T tmp = v[i];
      v[i] = v[j];
      v[j] = tmp;
      ++i;
      --j;
    } else if (!(v[pivot] < v[i])) {
      ++i;
    } else if (!(v[j] < v[pivot])) {
      --j;
    }
  }
  int new_pivot = i;
  if (v[i] < v[pivot]) {
    new_pivot = i;
  } else {
    new_pivot = i - 1;
  }
  T tmp = v[pivot];
  v[pivot] = v[new_pivot];
  v[new_pivot] = tmp;
  quick_sort_helper(v, start, new_pivot);
  quick_sort_helper(v, new_pivot + 1, end);
}

template <Ord T> void quick_sort(std::vector<T> &a) {
  quick_sort_helper(a, 0, a.size());
}

void counting_sort(std::vector<int> &a, int min, int max) {
  std::vector<int> counts(max - min, 0);
  for (auto x: a) {
    counts[x - min]++;
  }
  for (int ai = 0, i = min; i < max; i++) {
    while (counts[i] > 0) {
      a[ai] = i;
      counts[i]--;
      ai++;
    }
  }
}

void test_sort(
    void (*sort_func)(std::vector<int> &),
    const std::vector<int> &in,
    std::string name) {
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
  std::vector<int> v = {};
  std::vector<int> v0 = {5};
  std::vector<int> v1 = {5, 1, 3, 4, 2};
  std::vector<int> v2 = {5, 1, 10, 3, 4, 2, 25, 5, 8};
  std::vector<int> v3 = {1, 3, 2, 5, 4, 7, 6, 9, 8, 10};
  test_sort(bubble_sort<int>, v, "bubble_sort");
  test_sort(bubble_sort<int>, v0, "bubble_sort");
  test_sort(bubble_sort<int>, v1, "bubble_sort");
  test_sort(bubble_sort<int>, v2, "bubble_sort");
  test_sort(bubble_sort<int>, v3, "bubble_sort");
  test_sort(insertion_sort<int>, v, "insertion_sort");
  test_sort(insertion_sort<int>, v0, "insertion_sort");
  test_sort(insertion_sort<int>, v1, "insertion_sort");
  test_sort(insertion_sort<int>, v2, "insertion_sort");
  test_sort(insertion_sort<int>, v3, "insertion_sort");
  test_sort(heap_sort<int>, v, "heap_sort");
  test_sort(heap_sort<int>, v0, "heap_sort");
  test_sort(heap_sort<int>, v1, "heap_sort");
  test_sort(heap_sort<int>, v2, "heap_sort");
  test_sort(heap_sort<int>, v3, "heap_sort");
  test_sort(merge_sort<int>, v, "merge_sort");
  test_sort(merge_sort<int>, v0, "merge_sort");
  test_sort(merge_sort<int>, v1, "merge_sort");
  test_sort(merge_sort<int>, v2, "merge_sort");
  test_sort(merge_sort<int>, v3, "merge_sort");
  test_sort(quick_sort<int>, v, "quick_sort");
  test_sort(quick_sort<int>, v0, "quick_sort");
  test_sort(quick_sort<int>, v1, "quick_sort");
  test_sort(quick_sort<int>, v2, "quick_sort");
  test_sort(quick_sort<int>, v3, "quick_sort");
  test_sort([](auto a){ counting_sort(a, 0, 25); },
      v, "counting_sort");
  test_sort([](auto a){ counting_sort(a, 0, 25); },
      v0, "counting_sort");
  test_sort([](auto a){ counting_sort(a, 0, 25); },
      v1, "counting_sort");
  test_sort([](auto a){ counting_sort(a, 0, 50); },
      v2, "counting_sort");
  test_sort([](auto a){ counting_sort(a, 0, 25); },
      v3, "counting_sort");
  return 0;
}
