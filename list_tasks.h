#ifndef LIST_TASKS_H
#define LIST_TASKS_H

using namespace std;

// Task 1: Count same values in list

void counter(Node* head, int x)
{
    int count = 0;
    while (head != NULL) 
    {
        if (head->data == x)
        {
            count++;
        }
        head = head->next;
    }
    cout << x << " was in list " << count << " times" << endl;
}

// Task 2: Take value by index
void value_by_index(Node* head, int index)
{
    Node *counter = head;
    int count = 0;
    while (counter != NULL)
    {
        if (count == index)
        {
            cout << counter->data;
            return;
        }
        count++;
        counter = counter->next;
    }
    cout << "out of range" << endl;
}

// Task 3: delete whole list and set head ptr to NULL
void delete_list(Node** head)
{
    Node *temp = *head;
    Node *next;
    while (temp != NULL)
    {
        next = temp->next;
        delete temp;
        temp = next;
    }
    *head = NULL;
} 

// Task 4: Pop-function
int pop(Node** head)
{
    Node* temp = *head;
    if (temp != NULL)
    {
        int x = temp->data;
        temp = temp->next;
        delete *head;
        *head = temp;
        return x;
    }
    else 
    {
        cout << "list is empty" << endl;
        return -1;
    }    
}

// Task 5: insertNth() for list
void InsertNth(Node** headRef, int index, int data)
{
    Node *temp = *headRef;
    if (index == 0)
    {
        Node *newNode = new Node(data, temp);
        *headRef = newNode;
        return;
    }

    for (int i = 0; i < index-1; i++)
    {
        if (temp != NULL && temp->next != nullptr)
        {
            temp = temp->next;
        }
        else 
        {
            cout << "out of range!" << endl;
            return;
        }
    }
    Node *newNode = new Node(data, temp->next);
    temp->next = newNode;
}

// Task 6: Sorted Insert
void SortedInsert(Node** headRef, Node* newNode) 
{
    Node *temp = *headRef;
    if (temp == NULL || newNode->data < temp->data)
    {
        *headRef = newNode;
        newNode->next = temp;
        return;
    }

    while ((temp->next)->data <= newNode->data)
    {
        temp = temp->next;
        if (temp->next == nullptr)
        {
            temp->next = newNode;
            return;
        }

    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Task 7: InsertSort
void InsertSort(Node** headRef)
{
    Node *temp = *headRef;
    Node *sorted = NULL;
    while (*headRef != NULL)
    {
        *headRef = temp->next;
        temp->next = nullptr;
        SortedInsert(&sorted, temp);
        temp = *headRef;
    }
    *headRef = sorted;    
}


// Task 8: Append list B to the end of list A, then PtrB = NULL; 
void Append(Node** aRef, Node** bRef) 
{
    Node *temp1 = *aRef;
    if (*aRef == NULL)
    {
        *aRef = *bRef;
    }
    else if (*bRef != NULL)
    {
        while (temp1->next != nullptr)
        {
            temp1 = temp1->next;
        }
        temp1->next = *bRef;
    }
    *bRef = NULL;
}

// Task 9: FrontBackSplit - split in two parts; if odd -> turn extra element to the left side.
void FrontBackSplit(Node* source, 
    Node** frontRef, Node** backRef)
{
    delete_list(&(*frontRef));
    delete_list(&(*backRef));

    if (source == NULL)
    {
        *frontRef = NULL;
        *backRef = NULL;
        return;
    }
    if (source->next == nullptr)
    {
        *frontRef = source;
        *backRef = NULL;
    }

    Node *slow  = source;
    Node *fast = source->next;
    *frontRef = source;


    while (fast != NULL)
    {
        if (fast->next == nullptr)
        {
            break;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    *backRef = slow->next;
    slow->next = nullptr;
}

// Task 10: Remove duplicates
void removeDuplicates(Node *head)
{
    Node *temp = head;
    Node *save = NULL;
    while (temp->next != nullptr)
    {
        if ((temp->next)->data == temp->data)
        {
            save = temp->next;
            if ((temp->next)->next != nullptr)
            {
                temp->next = temp->next->next;
                delete save;
            }
            else
            {
                temp->next = nullptr;
                delete save;
                return;
            }
        }
        temp = temp->next;
    }
}

// Task 11: MoveNode - pop from B-list and push to A-list
void MoveNode(Node** destRef, Node** sourceRef)
{
    if ((*sourceRef) == NULL)
    {
        return;
    }
    push(&(*destRef), pop(&(*sourceRef)));    
}

// Task 12: Alternating Split - Just devide source in 2 lists (by MoveNode maybe) 
void AlternatingSplit(Node* source,
                    Node** aRef, Node** bRef)
{
    Node *a = NULL;
    Node *b = NULL;
    Node *current = source;
    while (current != NULL)
    {
        MoveNode(&a, &current);
        if (current != NULL)
        {
            MoveNode(&b, &current);
        }
    }
    *aRef = a;
    *bRef = b;
}

// Task 13: Shuffle Merge - Shuffle 2 lists like cards

Node* ShuffleMerge(Node* a, Node* b)
{
    Node *result = NULL;
    Node **tail = &result; 

    while(1)
    {
        if (a == NULL)
        {
            *tail = b;
            break;
        }
        else if (b == NULL)
        {
            *tail = a;
            break;
        }
        else 
        {
            MoveNode(tail, &a);
            tail = &((*tail)->next);
            MoveNode(tail, &b);
            tail = &((*tail)->next);
        }
    }
    return result;
}

// Task 14: SortedMerge without MoveNode
Node* SortedMerge(Node* list1, Node* list2) 
{
    Node *merged = NULL;
    Node *start = merged;

    while(1)
    {
        if (list1 == NULL && list2 != NULL)
        {
            if (merged == NULL)
            {
                start = list2;
                return start;
            }
            merged->next = list2;
            return start;
        }
        
        if (list2 == NULL && list1 != NULL)
        {
            if (merged == NULL)
            {
                start = list1;
                return start;
            }
            merged->next = list1;
            return start;
        }
        if (list2 == NULL && list1 == NULL)
        {
            return NULL;
        }

        if (list1->data <= list2->data)
        {
            if (merged == NULL)
            {
                merged = list1;
                start = merged;
                list1 = list1->next;
            }
            else
            {
                merged->next = list1;
                list1 = list1->next;
                merged = merged->next;
            }
        }
        else
        {
            if (merged == NULL)
            {
                merged = list2;
                start = merged;
                list2 = list2->next;
            }
            else
            {
                merged->next = list2;
                list2 = list2->next;
                merged = merged->next;
            }
        }
    }          
}

// Task 15: MergeSort - recursive sorting. FrontBackSplit, SortedMerge in use;
Node* MergeSort(Node* headRef)
{
    if (headRef->next != nullptr)
    {
        Node *a = NULL;
        Node *b = NULL;
        FrontBackSplit(headRef, &a, &b);
        a = MergeSort(a);
        b = MergeSort(b);
        headRef = SortedMerge(a, b);
        return headRef;
    }
    else
    {
        return headRef;
    }
}

// Task 16.1: SortedIntersect_1() - with tail and push. Don't touch the source A/B data
Node* SortedIntersect_1(Node* a, Node* b)
{
    Node *final = NULL; //final intersection
    Node **tail = &final; // last nullptr all time

    if (a == NULL || b == NULL)
    {
        final = NULL;
        return final;
    }

    while (1)
    {
        if (a->data > b->data)
        {
            b = b->next;
        }
        else if (b->data > a->data)
        {
            a = a->next;
        }

        if (a == NULL || b == NULL)
        {
            return final;
        }

        if (a->data == b->data)
        {
            push(&(*tail), a->data);
            tail = &((*tail)->next);
            a = a->next;
            b = b->next;

            if (a == NULL || b == NULL)
            {
                return final;
            }
        }  
    }
    return final;
}

// Task 16.2: SortedIntersect_2() - variation with no repeats in numbers
Node* SortedIntersect_2(Node* a, Node* b)
{
    Node *final = NULL; //final intersection
    Node **tail = &final; // last nullptr all time
    Node **temp = &final; // last element in final all time

    if (a == NULL || b == NULL)
    {
        final = NULL;
        return final;
    }

    while (1)
    {
        if (a->data > b->data)
        {
            b = b->next;
        }
        else if (b->data > a->data)
        {
            a = a->next;
        }

        if (a == NULL || b == NULL)
        {
            return final;
        }

        if ((*temp) != NULL)
        {
            if (a->data == b->data && ((*temp)->data == a->data))
            {  
                a = a->next;
                b = b->next;
                continue;
            }
        }
        if (a->data == b->data)
        {
            push(&(*tail), a->data);
            tail = &((*tail)->next);
            while ((*temp)->next != nullptr)
            {
                temp = &((*temp)->next);
            }
            a = a->next;
            b = b->next;

            if (a == NULL || b == NULL)
            {
                return final;
            }
        }  
    }
    return final;
}

// Task 17.1: Iterative reverse of the list - "3 pointers" Hint 
Node* Reverse_1(Node* head)
{
    Node *past, *mid, *next;
    past = NULL;
    mid = head;
    next = head->next;
    while(true)
    {
        if (past == NULL)
        {
            past = mid;
            past->next = NULL;
        }
        else {past = mid;}
        mid = next;
        next = next->next;
        if (next == NULL)
        {
            mid->next = past;
            head = mid;
            break;
        }
        mid->next = past;
    }
    return head;
}

// Task 17.2: "Pop-Push" reverse hint by MoveNode()
Node *Reverse_2(Node *head)
{
    Node *final = NULL;
    while (head != NULL) 
    {
        MoveNode(&final, &head);
    }
    return final;
}

// Task 18: Recursive Reverse
void Reverse_recur(Node **headRef)
{
    if (*headRef == NULL)
    {
        return;
    }

    Node *temp = *headRef;
    Node *go = temp->next;
    if (go != NULL)
    {
        Reverse_recur(&go);
        (temp->next)->next = temp;
        temp->next = NULL;
        *headRef = go;
    }
    else
    {
        return;
    }
}

#endif