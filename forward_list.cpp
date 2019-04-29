//  Created by Александр on 2/3/19.
//  Copyright © 2019 Александр. All rights reserved.

#include <iostream>
using namespace std;

//Template LIST
template<typename T>
class List
{
public:
    List();
    ~List();
    
    //Functions Prototypes
    void pushBack(T data);
    int getSize(){return Size;}
    T& operator[] (const int index);
    void popFront();
    void clear();
    void pushFront(T data);
    void popBack();
    void insert(T value, int index);
    void removeAt(int index);

private:
    //Template NODE
    template<typename T1> //VS T
    class Node
    {
    public:
        //VAR NODE
        Node* pNext;
        T Data;
        //Constructor NODE
        Node(T data = T(),Node* pNext = nullptr)
        //Параметр по умолчанию 0 для того что была возможность сделать последний элемент без указателя адресса и чтоб дата не была заплнена мусором
        {
            this->Data = data;
            this->pNext = pNext;
        }
        //Destructor NODE
        ~Node();
    };
    //VAR LIST
    int Size;
    Node<T> *head;
};

//Constructor LIST
template<typename T>
List<T>::List()
{
    Size = 0;
    head = nullptr;
}

//Destructor LIST
template<typename T>
List<T>::~List()
{
    //clear();
}

//PUSHBACK
template<typename T>
void List<T>::pushBack(T data)
{
    if(head == nullptr)
    {
        head = new Node<T>(data);
    }else
    {
        Node<T>* current = head;
        while(current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    Size++;
}

//PUSFRONT
template<typename T>
void List<T>::pushFront(T data)
{
    head = new Node<T>(data,head);
    Size++;
}

//INSERT
template<typename T>
void List<T>::insert(T value,int index)
{
    if(index == 0)
    {
        pushFront(value);
    }else
    {
        
        Node<T> *previous = head;
        for(int i = 0; i<index - 1; i++)
        {
            previous = previous->pNext;
        }
        Node<T> *newNode = new Node<T>(value,previous->pNext);
        previous->pNext = newNode;
        Size++;
    }
}

//REMOVE_AT
template<typename T>
void List<T>::removeAt(int index)
{
    if(index == 0)
    {
        popFront();
    }else
    {
        Node<T> *previous = head;
        for(int i = 0; i<index - 1; i++)
        {
            previous = previous->pNext;
        }
        Node<T> *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        Size--;
    }
}

//POPBACK
template<typename T>
void List<T>::popBack()
{
    removeAt(Size-1);
}

//Operator[]
template<typename T>
T & List<T>::operator[] (const int index)
{
    
    if(index > Size){
        cout<<"Non-valid index"<<endl;
        exit(0);
    }
    
    int counter = 0;
    
    Node<T> *current = head;
    
    while(current != nullptr)
    {
        if(counter == index)
        {
            return current->Data;
        }
        current = current->pNext;
        counter++;
    }
    return current->Data;
}

//POP_FRONT
template<typename T>
void List<T>::popFront()
{
    Node<T> *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

//CLEAR
template<typename T>
void List<T>::clear()
{
    while(Size)
    {
        popFront();
    }
}

//MAIN
int main(int argc, const char * argv[]) {
    
    List<int> list;
    list.pushBack(5);
//    list.pushBack(10);
//    list.pushBack(15);
    list.pushFront(7);
//    list.popFront();
//    list.clear();
    list.insert(100, 2);
    
    cout<< list.getSize()<<endl;
    cout<< list[2]<<endl;
//    list.removeAt(1);
    
    return 0;
}
