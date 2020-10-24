#include <stdio.h>
#include <iostream>
#include <time.h>

class Node {
public:
	int data;
	Node* previous;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
		this->previous = NULL;
	}

	~Node() {
		this->data = NULL;
		this->next = NULL;
		this->previous = NULL;
	}

	int getData() {
		return data;
	}

	void setData(int data) {
		this->data = data;
	}

	Node* getPrevious() {
		return previous;
	}

	void setPrevious(Node* previous) {
		this->previous = previous;
	}

	Node* getNext() {
		return next;
	}

	void setNext(Node* next) {
		this->next = next;
	}
};

class LinkedList {
public:
	Node* head;
	Node* tail;


	LinkedList() {
		this->head = NULL;
		this->tail = NULL;
	}

	~LinkedList() {
		clear();
	}

	Node* getHead() {
		return this->head;
	}

	Node* getTail() {
		return this->tail;
	}

	void printAll() {
		Node* temp = this->head;
		while (temp) {
			printf("%d \n", temp->getData());
			temp = temp->getNext();
		}
	}

	void add(int element) {
		Node* newNode = new Node(element);
		if (!this->head) {
			this->head = newNode;
			this->tail = newNode;
		} else {
			this->tail->setNext(newNode);
			newNode->setPrevious(this->tail);
		}
		this->tail = newNode;
	}

	void clear() {
		Node* current = this->head;
		while (current) {
			Node* next = current->next;
			delete current;
			current = next;
		}
		this->head = NULL;
		this->tail = NULL;
	}
};

void radix(int* a, int s) {
	size_t place = 16 * 16 * 16 * 16;
	LinkedList* list = new LinkedList[place];
	LinkedList* list2 = new LinkedList[place];

	Node* h;
	int c, i;

	for (i = 0; i < s; ++i) list[a[i] & 0xffff].add(a[i]);
	c = 0;
	for (int i = 0; i < 16*16*16*16; ++i) {
		h = list[i].getHead();
		while (h) {
			a[c] = h->getData();
			c++;
			h = h->getNext();
		}
	}

	for (i = 0; i < s; ++i) list2[(a[i] >> 16) & 0xffff].add(a[i]);
	c = 0;
	for (int i = 0; i < place; ++i) {
		h = list2[i].getHead();
		while (h) {
			a[c] = h->getData();
			c++;
			h = h->getNext();
		}
	}
}

int main() {
	size_t s = 10000000;
	int i, offset, j;
	int* B = (int*)malloc(sizeof(int) * s);
	if (B == NULL) return 0;

	time_t t;
	srand((unsigned)time(&t));
	offset = rand() % s;
	for (i = 0; i < s; i++)
	{
		B[i] = ((91 * i) % s) + offset;
	}

	printf("Prepared array of 10 million integers; calling sort\n");
	radix(B, s);
	printf("finished sort, now check result\n");
	for (i = 0, j = 0; i < s; i++)
		if (B[i] != i + offset) j++;
	if (j == 0)
		printf("Passed Test\n");
	else
		printf("Failed Test. %d numbers wrong.\n", j);
}