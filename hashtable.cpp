#include <vector>
#include <list>
#include <optional>
#include <utility>

template <typename K, typename V> class Hashtable {
public:
  Hashtable(int m, int (*hash_func)(const K &)) :
    m(m), hash_func(hash_func) {
      tbl = std::vector<std::list<std::pair<K,V>>>(m);
  }
  std::optional<V> search(K key);
  void insert(K key, V value);
  void remove(K key);
private:
  int m;
  int (*hash_func)(const K &);
  std::vector<std::list<std::pair<K,V>>> tbl;
};


template <typename K, typename V>
std::optional<V> Hashtable<K, V>::search(K key) {
  // TODO
  return {};
}

template <typename K, typename V>
void Hashtable<K, V>::insert(K key, V value) {
  // TODO
}

template <typename K, typename V>
void Hashtable<K, V>::remove(K key) {
  // TODO
}


int main() {
  return 0;
}
