// Muhammad_Yousaf_22i8797_F
#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T value;
    Node *next;
    Node(T &val)
    {
        this->value = val;
        this->next = nullptr;
    }
};

template <typename T>
class List
{
    Node<T> *head;

public:
    int last_index;
    List(const List<T> &other)
    {
        //this->~List(); //last change
        this->emptyTheList();
        head = nullptr;
        last_index = 0;

        Node<T> *otherCurrent = other.head;

        while (otherCurrent != nullptr)
        {
            T valueCopy = otherCurrent->value;
            insert(valueCopy);
            otherCurrent = otherCurrent->next;
        }
    }
    List()
    {
        head = nullptr;
        last_index = 0;
    }
    void emptyTheList()
    {
        if(this->isEmpty())
        return;

        Node<T> *temp = nullptr;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        last_index = 0;
    }
    ~List()
    {
        emptyTheList();
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void insert(T &val)
    {
        Node<T> *newNode = new Node<T>(val);

        if (isEmpty())
        {
            head = newNode;
        }
        else
        {
            Node<T> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }

        last_index++;
    }

    void remove(int ind)
    {
        if (isEmpty())
        {
            cout << "List is empty!" << endl;
        }
        else if (ind > last_index)
        {
            cout << ("Entered index is out of bounds! Entered index should be from 1 and " + to_string(last_index)) << endl;
        }
        else
        {
            Node<T> *current = head;
            Node<T> *prev = nullptr;

            if (ind == 1)
            {
                Node<T> *temp = head;
                head = head->next;
                delete temp;
                temp = nullptr;
            }
            else
            {
                for (int i = 1; i < ind; i++)
                {
                    prev = current;
                    current = current->next;
                }
                cout << "current value: " << current->value << endl;

                Node<T> *temp = current;
                prev->next = current->next;
                delete current;
                current = nullptr;
            }

            last_index--;
        }
    }

    T &getElement(int ind)
    {
        if (ind > last_index || ind <= 0)
        {
            cout << ("Entered index is out of bounds! Entered index should be from 1 and " + to_string(last_index)) << endl;
            exit(1);
        }
        else
        {
            Node<T> *current = head;

            for (int i = 1; i < ind; i++)
            {
                current = current->next;
            }
            return current->value;
        }
    }
    

    void print()
    {
        if (isEmpty())
            cout << "List is empty!" << endl;
        else
        {
            Node<T> *current = head;
            while (current != nullptr)
            {
                cout << current->value << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};
#endif