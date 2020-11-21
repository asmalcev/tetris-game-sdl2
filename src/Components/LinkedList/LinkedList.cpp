#include "LinkedList.hpp"
#include <iostream>

LinkedList::LinkedList() : 
  head(nullptr),
	tail(nullptr) {}

LinkedList::~LinkedList() {
	clear();
}

void LinkedList::clear() {
	while (head != nullptr) {
		tail = head->next;
		delete[] head->data;
		delete head;
		head = tail;
	}
	head = nullptr;
	tail = nullptr;
}

int LinkedList::getLength() {
  int length;
  Node * cur = head;
  while (cur = cur->next) length++;
	return length;
}

void LinkedList::remove(uchar * line) {
	if (head == nullptr) {
		return;
	}
	Node * cur = head;

	while (cur != nullptr) {
		if (cur->data == line) {
			if (cur->prev == nullptr) {
				if (tail->prev == nullptr) {
					delete head;
					tail = head = nullptr;
				} else {
					head = head->next;
					delete head->prev;
					head->prev = nullptr;
				}
			} else if (cur->next == nullptr) {
				tail = tail->prev;
				delete tail->next;
				tail->next = nullptr;
			} else {
				Node * prevEl = cur->prev;
				Node * nextEl = cur->next;
				prevEl->next = nextEl;
				nextEl->prev = prevEl;
				delete[] cur->data;
				delete cur;
			}
			return;
		}
		cur = cur->next;
	}
}

bool LinkedList::empty() {
	return head == nullptr;
}

void LinkedList::unshift(uchar * line) {
  Node * tmp = new Node;
	tmp->data = line;
	tmp->prev = nullptr;

	if (head == nullptr) {
		head = tail = tmp;
	} else {
		head->prev = tmp;
		tmp->next = head;
		head = head->prev;
	}
}

uchar * LinkedList::get(int index) {
	int i = 0;
	Node * cur = head;
	for (; i < index && cur->next; cur = cur->next, i++);
	if (i == index) {
		if (cur == nullptr) return nullptr;
		return cur->data;
	}
	return nullptr;
}