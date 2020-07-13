#ifndef LINKEDLIST_MPQ_H
#define LINKEDLIST_MPQ_H

#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;
template<typename T>
class Node; // class declaration

// doubly linked list node
template <typename T>
struct Node {
  T obj;
  int key;
  Node<T> *prev, *next;
  // constructor
  Node(T e = T(), int _key = 99, Node *p = nullptr, Node *n = nullptr)
    : obj(e), key(_key), prev(p), next(n) {}
};

// doubly linked list class
template<typename T>
struct LL_MPQ {
  Node<T> header, trailer;
  LL_MPQ<T>() : header(T()), trailer(T()) // default constructor
  { header.next = &trailer; trailer.prev = &header; } 
  bool is_empty() const { return header.next == &trailer; } //O(1)
  void insert(T obj, int key); 
  T remove_min(); // remove the first node
  void print() {
      Node<T> *current = header.next;
      cout << "----PRINT LIST----" << endl;

      while (current != &trailer) {
          cout << "Key: " << current->key << "   Job: " << current->obj.ID << endl; 
          current = current->next;
      }
      cout << " ----END PRINT----" << endl;
      return;
  }
};

template<typename T>
void LL_MPQ<T>::insert(T _obj, int _key) {
    if (this->is_empty()) {
        //cout << "Inserting into an empty list" << endl;
        Node<T> *newNode = new Node<T>(_obj, _key, &header, header.next);
        header.next = newNode;
    }
    else {
        Node<T> *current = &header;
        while (current->next->key <= _key) {
            if (current->next->key == _key && current->next->obj.ID > _obj.ID)
                break;
            current = current->next;
        }
        //cout << "Current: " << current->key << "   Inserting: " << _key << " after" << endl;
        Node<T> *newNode = new Node<T>(_obj, _key, current, current->next);
        current->next->prev = newNode;
        current->next = newNode;
        return;
    }
    return;
}

template<typename T>
T LL_MPQ<T>::remove_min() {
    Node<T> *current = &header;
    current = current->next;
    current->next->prev = current->prev;
    current->prev->next = current->next;
    T holder = current->obj;
    delete current;
    return holder;
}

#endif