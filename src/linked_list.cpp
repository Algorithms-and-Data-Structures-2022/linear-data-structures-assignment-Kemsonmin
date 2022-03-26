#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* new_node = new Node(value);
    if (size_ == 0) {
      front_ = new_node;
      back_ = new_node;
    }
    else {
      back_->next = new_node;
      back_ = new_node;
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index >= 0 && index <= size_) {
      Node* new_node = new Node(value);
      if (front_ == nullptr && index == 0) {
        front_ = new_node;
        back_ = new_node;
      }
      else if (index == 0) {
        new_node->next = front_;
        front_ = new_node;
      }
      else if (index == size_) {
        back_->next = new_node;
        back_ = new_node;
      }
      else {
        Node* curr_node = FindNode(index - 1);
        new_node->next = curr_node->next;
        curr_node->next = new_node;
      }
      size_ += 1;
      return true;
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index >= 0 && index < size_) {
      FindNode(index)->value = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 && index < size_) {
      size_ -= 1;
      if (index == 0) {
        int t = front_->value;
        Node* node_to_remove = front_;
        front_ = front_->next;
        delete node_to_remove;
        node_to_remove = nullptr;
        return t;
      }
      else {
        Node* curr_node = FindNode(index - 1);
        Node* node_to_remove = curr_node->next;
        int t = node_to_remove->value;
        curr_node->next = node_to_remove->next;
        delete node_to_remove;
        node_to_remove = nullptr;
        return t;
      }
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /* */) {
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= 0 && index < size_) {
      return FindNode(index)->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (FindNode(i)->value == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    for (int i = 0; i < size_; i++) {
      if (FindNode(i)->value == value) {
        return true;
      }
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= 0 && index < size_) {
      Node* curr_node = front_;
      for (int i = 0; i < index; i++) {
        curr_node = curr_node->next;
      }
      return curr_node;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment