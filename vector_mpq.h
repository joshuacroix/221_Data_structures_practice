#ifndef VECTOR_MPQ_H
#define VECTOR_MPQ_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct vector_object {
    int key;
    T value;
};

template <typename T>
struct MPQ {
    vector< vector_object<T> > MPQ_vector;
    T remove_min() {
        T ret_value = this->MPQ_vector[0].value;
        this->MPQ_vector.erase(MPQ_vector.begin());
        return ret_value;
    }
    bool is_empty() {
        if (this->MPQ_vector.size() == 0)
            return 1;
        return 0;
    }
    void insert(vector_object<T> _object) {
        int index = 0;
        if (this->is_empty()) {
            this->MPQ_vector.push_back(_object);
        }
        else {
            while (this->MPQ_vector[index].key <= _object.key && index < this->MPQ_vector.size()) {
                //cout << "Vector key: " << this->MPQ_vector[index].key << endl;
                //cout << "Object key: " << _object.key << endl;
                if (this->MPQ_vector[index].key == _object.key && this->MPQ_vector[index].value.ID > _object.value.ID) {
                    break;
                }
                index++;
            }
            this->MPQ_vector.insert(this->MPQ_vector.begin() + index, _object);
            //cout << "Insert at: " << index << endl;
        }
        return;
    }
    void print() {
        cout << endl << "ID: ";
        for (int i = 0; i < this->MPQ_vector.size(); i++) {
            cout << MPQ_vector[i].value.ID << " -> ";
        }
        cout << endl << "Length: ";
        for (int i = 0; i < this->MPQ_vector.size(); i++) {
            cout << MPQ_vector[i].value.length << " -> ";
        }
        cout << endl << "Priority: ";
        for (int i = 0; i < this->MPQ_vector.size(); i++) {
            cout << MPQ_vector[i].value.prior << " -> ";
        }
        cout << endl << endl;
    }
};

#endif
