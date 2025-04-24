#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>

#include "../s21_linked_list/s21_linked_list.h"

namespace s21 {

template <typename T, typename Container = linked_list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack &&s);

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  const_reference top();
  size_type size();
  bool empty();

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container container_;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif