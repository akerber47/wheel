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
  int i = this->hash_func(key);
  auto chain = this->tbl[i];
  for (auto it = chain.begin(); it != chain.end(); it++) {
    if (it->first == key) {
      return it->second;
    }
  }
  return {};
}

template <typename K, typename V>
void Hashtable<K, V>::insert(K key, V value) {
  int i = this->hash_func(key);
  auto chain = this->tbl[i];
  for (auto it = chain.begin(); it != chain.end(); it++) {
    if (it->first == key) {
      it->second = value;
      return;
    }
  }
  chain.insert(chain.end(), {key, value});
}

template <typename K, typename V>
void Hashtable<K, V>::remove(K key) {
  int i = this->hash_func(key);
  auto chain = this->tbl[i];
  for (auto it = chain.begin(); it != chain.end(); it++) {
    if (it->first == key) {
      chain.erase(it);
      return;
    }
  }
}


template <typename K, typename V> class Hashtable_open {
public:
  Hashtable_open(
      int m,
      int (*hash_func)(const K &),
      int (*probe_func)(int)) :
    m(m), hash_func(hash_func), probe_func(probe_func) {
      tbl = std::vector<std::optional<std::pair<K,V>>>(m);
  }
  std::optional<V> search(K key);
  void insert(K key, V value);
  void remove(K key);
private:
  int m;
  int (*hash_func)(const K &);
  int (*probe_func)(int);
  std::vector<std::optional<std::pair<K,V>>> tbl;
};

template <typename K, typename V>
std::optional<V> Hashtable_open<K, V>::search(K key) {
  int i = this->hash_func(key);
  for (int j = 0; j < this->m; j++) {
    auto &pair = this->tbl[i + this->probe_func(j)];
    if (pair && pair->first == key) {
      return pair->second;
    }
  }
  return {};
}

template <typename K, typename V>
void Hashtable_open<K, V>::insert(K key, V value) {
  int i = this->hash_func(key);
  for (int j = 0; j < this->m; j++) {
    auto &pair = this->tbl[i + this->probe_func(j)];
    if (pair && pair->first == key) {
      pair->second = value;
    } else if (!pair) {
      *pair = {key, value};
    }
  }
}

template <typename K, typename V>
void Hashtable_open<K, V>::remove(K key) {
  int i = this->hash_func(key);
  for (int j = 0; j < this->m; j++) {
    auto &pair = this->tbl[i + this->probe_func(j)];
    if (pair->first == key) {
      pair = {};
    }
  }
}

int main() {
  Hashtable<int, int> x(50, [](const int &x){ return x % 50; });
  x.search(2);
  x.insert(0, 5);
  x.search(0);
  x.remove(0);
  Hashtable_open<int, int> y(
      50,
      [](const int &x){ return x % 50; },
      [](int x){ return x;}
  );
  y.search(2);
  y.insert(0, 5);
  y.search(0);
  y.remove(0);
  return 0;
}
