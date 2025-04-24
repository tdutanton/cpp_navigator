#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>

#include "../s21_linked_list/s21_linked_list.h"

namespace s21 {

template <typename T, typename Container = s21::linked_list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();  // default constructor, creates empty queue
  queue(std::initializer_list<value_type> const &items);  // init list
  queue(const queue &q);
  queue(queue &&q);  // move constructor
  ~queue();
  queue &operator=(queue &&q);  // assignment operator overload for moving

  const_reference front();
  const_reference back();

  size_type size();
  bool empty();

  void push(const_reference value);  // inserts element at the end
  void pop();                        // remove first elem
  void swap(queue &other);           // swaps the contents

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container container_;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif