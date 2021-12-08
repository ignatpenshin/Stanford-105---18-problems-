#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node() : data(-1), next(nullptr) {};
    Node(int x) : data(x), next(nullptr) {};
    Node(int x, Node *next) : data(x), next(next) {};
};


void push(Node **head, int x)
{
    Node *header = new Node(x);
    header->next = *head;
    *head = header;
}

void append(Node *head, int x)
{
    Node *header = new Node(x);
    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = header;
}

void del_by_index(Node **head, int x)
{
    Node *header = *head;

    if (x == 0)
    {
        *head = header->next;
        delete header;
    }
    else 
    {
        for (int i = 0; i <= x-2; ++i)
        {
            if (header != NULL && header->next != nullptr)
            {
            header = header->next;
            }
            else
            {
                cout << "Out of list " << x << endl;
                return;
            }
        }

        Node *temp = header->next->next;
        Node* tempo = header->next;

        if (temp != nullptr)
        {
            delete tempo;
            header->next = temp; 
        }
        else 
        {
            delete tempo;
            header->next = nullptr;
        }
    }
}


void del_by_val(Node **head, int x) // remove all same values
{
    Node *prev = NULL;
    Node *current = *head;

    if (current == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }

    while (current->next != nullptr)
    {
        if (current->data == x)
        {
            if (prev == NULL)
            {
                *head = current->next;
                delete current;
                current = *head;
                continue;
            }
            else 
            {
                prev->next = current->next;
                delete current;
                current = prev->next;     
                continue;     
            }
        }
        prev = current;
        current = current->next;
    }
    if (current->data == x)
    {
        if (prev != NULL)
        {
            prev->next = nullptr;
            delete current;
        }
        else 
        {
            *head = NULL;
            delete current;
        }
    }
}

void print(Node *head, int index = -1)
{
    if (head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }

    if (index == -1)
    {
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
    }
    else
    {

        for (int i = 0; i < index; ++i)
        {
            head = head->next;
            if (head == NULL)
            {
                cout << "Index is bigger than list" << endl;
                return;
            }
        }
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else {cout << head->data << endl;}
    }
}


#endif

