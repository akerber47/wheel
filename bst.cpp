#include <vector>
#include <iostream>
#include <optional>
#include "common.h"

template <Ord K, typename V> struct BST_node {
  K key;
  V value;
  BST_node<K,V> *left;
  BST_node<K,V> *right;
};

template <Ord K, typename V> class BST {
public:
  std::optional<V> search(K key);
  void insert(K key, V value);
  void remove(K key);
private:
  BST_node<K,V> *root = nullptr;
};

template <Ord K, typename V>
std::optional<V> search_helper(BST_node<K,V> *n, K key) {
  if (n == nullptr) {
    return {};
  } else if (key == n->key) {
    return n->value;
  } else if (key < n->key) {
    return search_helper(n->left, key);
  } else {
    return search_helper(n->right, key);
  }
}

template <Ord K, typename V>
std::optional<V> BST<K, V>::search(K key) {
  return search_helper<K,V>(this->root, key);
}

template <Ord K, typename V>
void BST<K, V>::insert(K key, V value) {
  // TODO
}

template <Ord K, typename V>
void BST<K, V>::remove(K key) {
  // TODO
}

int main() {
  return 0;
}
