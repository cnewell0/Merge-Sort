/*
 * Cade Newell
 * CPSC 346:02
 * Project 1
 */


#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

/*
 * pushes the values I created in my array into my linked list
 */
void push(struct node **head, int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;

}

/*
 * Prints out the sorted linked list one number at a time on a new line
 */
void printlist(struct node *node)
{
    while(node != NULL)
    {
        printf("%d\n", node -> data);
        node = node -> next;
    }
    printf("\n");
}

/*
 * After the linked list is split it merges the numbers together based on which
 *      number is smallest and putting that at the front of the list
 */
struct node* merge(struct node* head1, struct node* head2){
    struct node* result = NULL;
    if (head1 == NULL){
        result = head2;
    }
    else if(head2 == NULL){
        result = head1;
    }

    else if (head1 -> data <= head2 -> data) {
        result = head1;
        result->next = merge(head1->next, head2);
    }
    else {

        result = head2;
        result->next = merge(head1, head2->next);
    }
    return result;
}
/*
 * Finds the length of the linked list to be used in
 *      the split function
 */
int getLength(struct node* head1) {
    int count = 0;
    struct node* h = head1;
    while (h != NULL) {
        count++;
        h = h->next;
    }
    return count;
}

/*
 * Repeatedly splits the linked list from the middle into two parts
 */
void split(struct node* source,
           struct node** front, struct node** back)
{
    int middle = getLength(source) / 2;
    *front = source;
    for (int i = 0; i < middle - 1; i++) {
        source = source->next;
    }
    *back = source->next;
    source->next = NULL;
}
/*
 * Calls the split function, checks the edge cases and then merges
 *      the lists into one list in sorted order
 */
struct node* mergeSort(struct node* head){
    struct node* front = NULL;
    struct node* back = NULL;


    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }

    split(head, &front, &back);

    front = mergeSort(front);
    back = mergeSort(back);

    return merge(front, back);
}


/*
 * Pushes the keys into node "head", calls the mergeSort function
 *      and prints the sorted list
 */
int main(void) {

    int keys[] = { 6, 8, 4, 3, 1, 9, 10 , 7, 22, 109, 33};
    int n = sizeof(keys)/sizeof(keys[0]);

    struct node *head = NULL;
    for (int i = 0; i < n; i++) {
        push(&head, keys[i]);
    }
    printf("Original List: ");
    printf("\n");
    printlist(head);

    head = mergeSort(head);

    printf("Sorted List: ");
    printf("\n");
    printlist(head);

}



