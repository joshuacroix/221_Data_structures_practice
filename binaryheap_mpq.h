#ifndef BINARYHEAP_MPQ_H
#define BINARYHEAP_MPQ_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
struct MPQ_object {
    int key;
    T value;
};

template <typename T>
struct BH_MPQ {
    vector< MPQ_object<T> > MPQ_heap;
    int parent(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return (2 * i + 1);
    }
    int right(int i) {
        return (2 * i + 2);
    }
    void sortdown(int i) {
        int left_child = left(i);
        int right_child = right(i);
        int lowest_value = i;
        //cout << "Sort Down" << endl;
        //if (i != 0) 
            //cout << "Parent: " << MPQ_heap[parent(i)].key << endl;
        //cout << "Left child: " << MPQ_heap[left_child].key << endl;
        //cout << "Right child: " << MPQ_heap[right_child].key << endl;

        if (left_child < MPQ_heap.size() && (MPQ_heap[left_child].key < MPQ_heap[i].key || (MPQ_heap[left_child].value.ID == MPQ_heap[i].value.ID && MPQ_heap[left_child].value.ID < MPQ_heap[i].value.ID))) {
            //cout << "Left child is lower" << endl;
            lowest_value = left_child;
        }
        if (right_child < MPQ_heap.size() && (MPQ_heap[right_child].key < MPQ_heap[lowest_value].key || (MPQ_heap[right_child].value.ID == MPQ_heap[lowest_value].value.ID && MPQ_heap[right_child].value.ID < MPQ_heap[lowest_value].value.ID))) {
            //cout << "Right child is picked" << endl;
            lowest_value = right_child;
        }
        if (lowest_value != i) {
            //cout << "Swapping " << MPQ_heap[i].key << " and " << MPQ_heap[lowest_value].key << endl;
            swap(MPQ_heap[i], MPQ_heap[lowest_value]);
            sortdown(lowest_value);
        }
    }
    void sortup(int i) {
        if (i && MPQ_heap[parent(i)].key > MPQ_heap[i].key) {
            //cout << "Swapping " << MPQ_heap[i].key << " and " << MPQ_heap[parent(i)].key << endl;
            swap(MPQ_heap[i], MPQ_heap[parent(i)]);
            sortup(parent(i));
        }
    }

    T remove_min() {
        T ret_value;
        //cout << "remove min" << endl;
        if (MPQ_heap.size() >= 1) {
            ret_value = this->MPQ_heap[0].value;
            //cout << "Swapping " << MPQ_heap[0].key << " with " << MPQ_heap[MPQ_heap.size()].key << endl;
            swap(MPQ_heap[0], MPQ_heap.back());
            MPQ_heap.pop_back();
        }
        sortdown(0);
        return ret_value;
    }
    bool is_empty() {
        if (this->MPQ_heap.size() == 0)
            return 1;
        return 0;
    }
    void insert(MPQ_object<T> _object) {
        int index = MPQ_heap.size();
        MPQ_heap.push_back(_object);
        //cout << "Inserting and sorting for " << MPQ_heap[index].key << endl;
        sortup(index);
        return;
    }
    void print() {
        cout << "Keys: ";
        for (int i = 0; i < this->MPQ_heap.size(); i++) {
            cout << MPQ_heap[i].key << " | ";
        }
        cout << endl << "Job ID: ";
        for (int i = 0; i < this->MPQ_heap.size(); i++) {
            cout << MPQ_heap[i].value.ID << " | ";
        }
        cout << endl;
    }
};
//2, 4, 8, 9, 10, 5, 3, 7, 1, 62
#endif