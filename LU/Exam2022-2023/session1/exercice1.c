#include <stdio.h>
#include <stdlib.h>

// create the list node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// function to create a node and append to list
void createNode(Node** head) {
    int value;
    printf("Enter the integer you want to add to the list: ");
    scanf("%d", &value);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    // if list is empty, newNode becomes head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // otherwise, append to end
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}
//reverse list
void reverseList(Node **b){
    Node *prev = NULL;
    Node *current = *b;
    Node *next = NULL;
    if(current == NULL) return;
    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *b = prev;
}
// function to print the list
void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main() {
    Node *head = NULL;

    createNode(&head);  // add some nodes
    createNode(&head);
    createNode(&head);

    printf("Original list:\n");
    printList(head);

    reverseList(&head);

    printf("Reversed list:\n");
    printList(head);

    return 0;
}



