#include "s21_linked_list.h"

namespace s21 {

template <typename T>
linked_list<T>::linked_list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
linked_list<T>::linked_list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const value_type &item : items) {
    push_back(item);
  }
}

template <typename T>
linked_list<T>::linked_list(const linked_list &q)
    : head_(nullptr), tail_(nullptr), size_(0) {
  copy(q);
}

template <typename T>
linked_list<T>::linked_list(linked_list &&q)
    : head_(nullptr), tail_(nullptr), size_(0) {
  copy(q);

  while (!q.empty()) q.pop();
}

template <typename T>
linked_list<T>::~linked_list() {
  while (!empty()) pop();
}

template <typename T>
linked_list<T> &linked_list<T>::operator=(linked_list &&q) {
  copy(q);
  while (!q.empty()) q.pop();

  return *this;
}

template <typename T>
typename linked_list<T>::const_reference linked_list<T>::front() {
  return head_->data_;
}

template <typename T>
typename linked_list<T>::const_reference linked_list<T>::back() {
  return tail_->data_;
}

template <typename T>
bool linked_list<T>::empty() {
  return head_ == nullptr;
}

template <typename T>
typename linked_list<T>::size_type linked_list<T>::size() {
  return size_;
}

template <typename T>
void linked_list<T>::pop() {
  if (head_) {
    Node *nextNode = head_;
    head_ = nextNode->next_;
    size_--;
    delete nextNode;
  }
}

template <typename T>
void linked_list<T>::push_back(const_reference value) {
  Node *newNode = new Node;
  newNode->data_ = value;
  newNode->next_ = nullptr;
  if (!head_) {
    head_ = newNode;
  }
  if (tail_) {
    tail_->next_ = newNode;
  }
  tail_ = newNode;
  size_++;
}

template <typename T>
void linked_list<T>::push_front(const_reference value) {
  Node *newNode = new Node;
  newNode->data_ = value;
  newNode->next_ = head_;
  head_ = newNode;
  if (!tail_) tail_ = newNode;
  size_++;
}

template <typename T>
void linked_list<T>::swap(linked_list &other) {
  std::swap(this->size_, other.size_);
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
}

template <typename T>
void linked_list<T>::copy(const linked_list &s) {
  Node *tail = nullptr;
  for (Node *n = s.head_; n != nullptr; n = n->next_) {
    Node *current = new Node;
    current->data_ = n->data_;
    current->next_ = nullptr;

    if (!head_) {
      head_ = current;
    } else {
      tail->next_ = current;
    }
    tail = current;
  }
  size_ = s.size_;
}

}  // namespace s21