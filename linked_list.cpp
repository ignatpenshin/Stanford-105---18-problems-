#include "linked_list.h"
#include "list_tasks.h"

using namespace std;

int main()
{
    Node *A = new Node(1); 
    append(A, 4);
    append(A, 6);
    append(A, 8);
    append(A, 10);
    print(A);



    Reverse_recur(&A);
    print(A);


    return 0;
}