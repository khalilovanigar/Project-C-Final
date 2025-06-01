#pragma once
#include<iostream>
#include<cassert>
#include<string>
using namespace std;
template <class T>
class DoubleLinkedList{
    class Node{
        public:
        T data;
        Node* prev;
        Node* next;
        Node(const T& data){
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
public:
    void AddBegin(const T& data){
        Node* node = new Node(data);
        if(head == nullptr){
            head = tail = node;
        }
        else{
            head->prev = node;
            node->next = head;
            head = node;
        }
        size++;
    }

    void AddEnd(const T& data){
        Node* node = new Node(data);
        if(tail == nullptr){
            head = tail = node;
        }
        else{
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        size++;
    }

    void AddIndex(const T& data,int index){
        if(index > size -1 || index < 0){
            assert(!"Index is wrong");
        }
        else if (index == 0){
            AddBegin(data);
        }
        else if (index == size -1 ){
            AddEnd(data);
        }
        else{
            Node* new_node = new Node(data);
            Node* current_node = head;
            for (size_t i = 0; i < index; i++)
            {
                current_node = current_node->next;
            }
            new_node->prev = current_node->prev;
            current_node->prev->next = new_node;
            current_node->prev = new_node;
            new_node->next = current_node;
            size++;
        }
    }

    void DeleteBegin(){
        if( head == nullptr){
            assert(!"List is empty");
        }
        else{
            Node* temp = head;
            if( head == tail){
                head = tail = nullptr;
            }
            else{
                head = head->next;
                head->prev = nullptr;
            }
            delete temp;
            size--;
        }
    }

    void DeleteEnd(){
        if(tail ==  nullptr){
            assert(!"List is empty");
        }
        else{
            Node* temp = tail;
            if(head == tail){
                head = tail = nullptr;
            }
            else{
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
            size--;
        }
    }

    void DeleteIndex(int index){
        if(index < 0 || index > size - 1){
            assert(!"Index is wrong");
        }
        else if(index == 0){
            DeleteBegin();
        }
        else if(index == size - 1){
            DeleteEnd();
        }
        else{
            Node* current_node = head;
            for (size_t i = 0; i < index; i++)
            {
                current_node = current_node->next;
            }
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;
            delete current_node;
        }
    }

    T& operator[](int index){
        if(index < 0 || index >= size){
            assert(!"Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    int Size()const{
        return size;
    }

    void Print()const{
        Node* current = head;
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~DoubleLinkedList(){
        Node* current = head;
        while(current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

};
