#pragma once

typedef unsigned char uchar;

struct Node {
	uchar * data;
	Node * next;
	Node * prev;
};

struct LinkedList {
	Node * head;
	Node * tail;

	LinkedList();
	~LinkedList();
	void clear();
	int getLength();
	void unshift(uchar *);
	void remove(uchar *);
	bool empty();
	uchar * get(int);
};