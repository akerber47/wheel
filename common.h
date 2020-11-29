// Print helpers
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

// Debug helpers
bool DEBUG = false;

void setdebug() {
  DEBUG = true;
}

template <Printable T> void do_debug(std::string tag, T v) {
  if (DEBUG) {
    std::cout << "dbg: " << tag << v << std::endl;
  }
}

template <Printable T> void do_debugv(std::string tag, std::vector<T> v) {
  if (DEBUG) {
    std::cout << "dbg: " << tag;
    pv<T>(v);
    std::cout << std::endl;
  }
}

void dbg(std::string tag, std::string s) {
  do_debug<std::string>(tag, s);
}

void dbg(std::string tag, int x) {
  do_debug<int>(tag, x);
}

void dbg(std::string tag, std::vector<int> v) {
  do_debugv<int>(tag, v);
}
