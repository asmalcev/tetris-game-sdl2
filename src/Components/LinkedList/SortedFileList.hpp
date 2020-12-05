#pragma once
#include <string>
#include <fstream>
#include <functional>
#include <stdio.h>

template <typename T>
class SortedFileList {
protected:
  struct Node {
    T data;
    Node * next;
  };

  std::string filePath;
  Node * head, * cur;
  std::function<int(T, T)> compare;
  size_t limitLength;

  void fixLimited(Node * tmp, size_t counter) {
    Node * cur = tmp;
    size_t i = counter;
    while (i < limitLength - 1 && cur->next) {
      cur = cur->next;
      i++;
    }
    if (i == limitLength - 1 && cur->next) {
      delete cur->next;
      cur->next = nullptr;
    }
  }

public:
  SortedFileList(
    const char * fileName,
    std::function<int(T, T)> compare,
    size_t limit
  ) : head(nullptr),
      compare(compare),
      limitLength(limit),
      filePath(fileName) {
    std::ifstream ifile(filePath, std::ios::in | std::ios::binary);
    if (ifile.is_open()) {
      T tmp;
      while ( !ifile.eof() ) {
        ifile.read((char *) &tmp, sizeof(T));
        addData(tmp);
      }
      ifile.close();
    }
  }

  ~SortedFileList() {
    Node * tmp;
    while (head != nullptr) {
      tmp = head->next;
      delete head;
      head = tmp;
    }
  }

  void addData(T data) {
    Node * tmp = new Node;
    tmp->data = data;
    tmp->next = nullptr;
    if (head == nullptr) {
      head = tmp;
    } else if (compare(head->data, tmp->data) != 1) {
      tmp->next = head;
      head = tmp;
      fixLimited(tmp, 1);
    } else {
      size_t counter = 0;
      Node * cur = head;
      while (
        cur->next != nullptr &&
        compare(cur->next->data, tmp->data) == 1
      ) {
        cur = cur->next;
        counter++;
      }
      tmp->next = cur->next;
      cur->next = tmp;
      fixLimited(tmp, counter + 1);
    }
  }

  void save() {
    std::ofstream ofile(filePath, std::ios::binary | std::ios::trunc);
    Node * cur = head;
    while (cur) {
      ofile.write((char *) &cur->data, sizeof(T));
      cur = cur->next;
    }
    ofile.close();
  }

  T * next() {
    if (cur->next) {
      cur = cur->next;
      return &cur->data;
    }
    return nullptr;
  }

  T * getCur() {
    if (cur) {
      return &cur->data;
    }
    return nullptr;
  }

  T * restart() {
    cur = head;
    if (cur) {
      return &cur->data;
    }
    return nullptr;
  }
};