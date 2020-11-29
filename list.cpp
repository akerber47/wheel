// Circular doubly linked list

template <typename T> struct List_link {
  T value;
  List_link<T> *next;
  List_link<T> *prev;
};

template <typename T> class List {
public:
  List() {
    head.next = &this->head;
    head.prev = &this->head;
  }
  List_link<T> *search(T value) const;
  List_link<T> *insert(T value);
  void remove(List_link<T> *elt);

private:
  List_link<T> head;
};

template <typename T>
List_link<T> *List<T>::search(T value) const {
  for (List_link<T> *x = this->head.next; x != &this->head; x = x->next) {
    if (x->value == value) {
      return x;
    }
  }
  return nullptr;
}

template <typename T>
List_link<T> *List<T>::insert(T value) {
  List_link<T> *x = new List_link<T>;
  List_link<T> *last = this->head.prev;
  last->next = x;
  this->head.prev = x;
  x->next = &this->head;
  x->prev = last;
  x->value = value;
  return x;
}

template <typename T>
void List<T>::remove(List_link<T> *x) {
  x->prev->next = x->next;
  x->next->prev = x->prev;
  delete x;
}

int main() {
  List<int> lst1;
  lst1.insert(0);
  auto p1 = lst1.search(1);
  auto p0 = lst1.search(0);
  lst1.remove(p0);
  return 0;
}

