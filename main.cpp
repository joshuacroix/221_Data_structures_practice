#include "linkedlist_mpq.h"
#include "binaryheap_mpq.h"
#include "vector_mpq.h"

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ctime>

struct CPU_Job {
    int ID;
    int length;
    int prior;
    CPU_Job(int a = 0, int b = 0, int c = 0) : ID(a), length(b), prior(c) {};
    bool operator<(const CPU_Job& job) {
        return true;
    }
};

int main () {
    CPU_Job(12345, 5, 2);
    BH_MPQ<CPU_Job> binary_heap_mpq;
    MPQ<CPU_Job> vector_mpq;
    LL_MPQ<CPU_Job> linked_list_mpq;

    while (true) {
        int type_input = 0;
        int num_input = 0;
        cout << "Please enter [1]: Vector, [2]: Linked List, [3]: Binary Heap, [0]: Quit  ==> ";
        cin >> type_input;
        if (type_input == 0)
            break;
        cout << "Please enter [1]: 1,000   [2]: 10,000    [3]: 100,000     [0]: Quit  ==> ";
        cin >> num_input;
        clock_t t1, t2;
        t1 = clock(); //start of clock
        string file_name = ""; //input
        if (num_input == 1)
            file_name = "SetSize1000.txt";
        else if (num_input == 2)
            file_name = "SetSize10000.txt";
        else if (num_input == 3)
            file_name = "SetSize100000.txt";
        else if (num_input == 0) 
            break;
        if (type_input == 1) {
            fstream cpu_job_list;
            int line_data;
            int ID = 0;
            int length = 0;
            int prior = 0;
            int count = 0;
            cpu_job_list.open(file_name, ios::in);
            while (cpu_job_list >> line_data) {
                //cout << line_data << endl;
                if (count == 0) {
                    ID = line_data;
                    count++;
                    //cout << "ID: " << ID << endl;
                }
                else if (count == 1) {
                    length = line_data;
                    count++;
                    //cout << "length: " << length << endl;    
                }
                else if (count == 2) {
                    prior = line_data;
                    count = 0;
                    //cout << "priority: " << prior << endl;
                    CPU_Job new_job(ID, length, prior);
                    vector_object<CPU_Job> job_holder;
                    job_holder.key = prior;
                    job_holder.value = new_job;
                    vector_mpq.insert(job_holder);
                }
            }
            //cout << "Data loaded, continue with processing? [y/n]" << endl;
            string answer = "y";
            //cin >> answer;
            if (answer == "y") {
                ofstream output_file; //open output file
                output_file.open("CPU.txt");
                while (vector_mpq.is_empty() == false) {
                    if (vector_mpq.MPQ_vector[0].value.length > 0) {
                        output_file << "Job " << vector_mpq.MPQ_vector[0].value.ID << " with length " << vector_mpq.MPQ_vector[0].value.length << " and priority " << vector_mpq.MPQ_vector[0].value.prior << endl;
                        vector_mpq.MPQ_vector[0].value.length = vector_mpq.MPQ_vector[0].value.length -1;
                    }
                    else {
                        vector_mpq.remove_min();
                    }
                }
                output_file << "No more jobs to run" << endl;
                output_file.close();

            }
            else {
                vector_mpq.print();
            }
        } //End of vector implementation
        else if (type_input == 2) { //Linked List
            fstream cpu_job_list;
            int line_data;
            int ID = 0;
            int length = 0;
            int prior = 0;
            int count = 0;
            cpu_job_list.open(file_name, ios::in);
            while (cpu_job_list >> line_data) {
                //cout << line_data << endl;
                if (count == 0) {
                    ID = line_data;
                    count++;
                    //cout << "ID: " << ID << endl;
                }
                else if (count == 1) {
                    length = line_data;
                    count++;
                    //cout << "length: " << length << endl;    
                }
                else if (count == 2) {
                    prior = line_data;
                    count = 0;
                    //cout << "priority: " << prior << endl;
                    CPU_Job new_job(ID, length, prior);
                    linked_list_mpq.insert(new_job, prior);
                }
            }
            //cout << "Data loaded, continue with processing? [y/n]" << endl;
            string answer = "y";
            //cin >> answer;
            if (answer == "y") {
                ofstream output_file; //open output file
                output_file.open("CPU.txt");
                Node<CPU_Job>* current = linked_list_mpq.header.next;
                while (linked_list_mpq.is_empty() == false) {
                    if (current != nullptr && current->obj.length > 0) {
                        output_file << "Job " << current->obj.ID << " with length " << current->obj.length << " and priority " << current->obj.prior << endl;
                        current->obj.length = current->obj.length - 1;
                    }
                    else {
                        current = current->next;
                        linked_list_mpq.remove_min();
                        
                    }
                }
                output_file << "No more jobs to run" << endl;
                output_file.close();
            }
            else {
                linked_list_mpq.print();
            }
            //vector_mpq.print();
        } //End of linked list implementation
        else if (type_input == 3) { //Binary heap
            fstream cpu_job_list;
            int line_data;
            int ID = 0;
            int length = 0;
            int prior = 0;
            int count = 0;
            cpu_job_list.open(file_name, ios::in);
            while (cpu_job_list >> line_data) {
                //cout << line_data << endl;
                if (count == 0) {
                    ID = line_data;
                    count++;
                    //cout << "ID: " << ID << endl;
                }
                else if (count == 1) {
                    length = line_data;
                    count++;
                    //cout << "length: " << length << endl;    
                }
                else if (count == 2) {
                    prior = line_data;
                    count = 0;
                    //cout << "priority: " << prior << endl;
                    CPU_Job new_job(ID, length, prior);
                    //linked_list_mpq.insert(new_job, prior);
                    MPQ_object<CPU_Job> job_holder;
                    job_holder.key = prior;
                    job_holder.value = new_job;
                    binary_heap_mpq.insert(job_holder);
                }
            }
            //cout << "Data loaded, continue with processing? [y/n]" << endl;
            string answer = "y";
            //cin >> answer;
            if (answer == "y") {
                ofstream output_file; //open output file
                output_file.open("CPU.txt");
                while (binary_heap_mpq.is_empty() == false) {
                    if (binary_heap_mpq.MPQ_heap[0].value.length > 0) {
                        output_file << "Job " << binary_heap_mpq.MPQ_heap[0].value.ID << " with length " << binary_heap_mpq.MPQ_heap[0].value.length << " and priority " << binary_heap_mpq.MPQ_heap[0].value.prior << endl;
                        binary_heap_mpq.MPQ_heap[0].value.length = binary_heap_mpq.MPQ_heap[0].value.length -1;
                    }
                    else {
                        binary_heap_mpq.remove_min();
                        //binary_heap_mpq.print();
                    }
                }
                output_file << "No more jobs to run" << endl;
                output_file.close();
            }
            else {
                binary_heap_mpq.print();
            }
            //vector_mpq.print();
        }
        t2 = clock(); //clock stop
        double diff = (double)(t2 -t1)*1000/CLOCKS_PER_SEC;
        cout << "Timing: " << diff << " milisec" << endl;
    }

    return 1;
}