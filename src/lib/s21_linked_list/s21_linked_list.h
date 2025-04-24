#ifndef S21_LINKED_LIST_H
#define S21_LINKED_LIST_H

#include <iostream>

namespace s21 {

template <typename T>
class linked_list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  linked_list();  // default constructor, creates empty linked_list
  linked_list(std::initializer_list<value_type> const &items);  // init list
  linked_list(const linked_list &q);  // copy constructor
  linked_list(linked_list &&q);       // move constructor
  ~linked_list();                     // destructor
  linked_list &operator=(
      linked_list &&q);  // assignment operator overload for moving object

  const_reference front();  // access the first element
  const_reference back();   // access the last element

  bool empty();
  size_type size();

  void push_back(const_reference value);   // inserts element at the end
  void push_front(const_reference value);  // inserts element at the top

  void pop();                     // remove first elem
  void swap(linked_list &other);  // swaps the contents

  void copy(const linked_list &q);

 private:
  typedef struct Node {
    value_type data_;
    Node *next_;
  } Node;

  Node *head_;
  Node *tail_;
  size_type size_;
};

}  // namespace s21

#include "s21_linked_list.tpp"

#endif