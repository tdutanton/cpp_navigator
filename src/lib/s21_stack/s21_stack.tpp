#include "s21_stack.h"

namespace s21 {

template <typename T, typename Container>
stack<T, Container>::stack() : container_() {}

template <typename T, typename Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : container_(items) {}

template <typename T, typename Container>
stack<T, Container>::stack(const stack &s) : container_(s.container_) {}

template <typename T, typename Container>
stack<T, Container>::stack(stack &&s) : container_(std::move(s.container_)) {}

template <typename T, typename Container>
stack<T, Container>::~stack() {}

template <typename T, typename Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&s) {
  if (this != &s) {
    container_ = std::move(s.container_);
    while (!s.empty()) s.pop();
  }
  return *this;
}

template <typename T, typename Container>
bool stack<T, Container>::empty() {
  return container_.empty();
}

template <typename T, typename Container>
typename stack<T, Container>::size_type stack<T, Container>::size() {
  return container_.size();
}

template <typename T, typename Container>
void stack<T, Container>::push(const_reference value) {
  container_.push_front(value);
}

template <typename T, typename Container>
void stack<T, Container>::pop() {
  container_.pop();
}

template <typename T, typename Container>
void stack<T, Container>::swap(stack &other) {
  container_.swap(other.container_);
}

template <typename T, typename Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() {
  return container_.front();
}

template <typename T, typename Container>
template <typename... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  (container_.push_back(std::forward<Args>(args)), ...);
}

}  // namespace s21