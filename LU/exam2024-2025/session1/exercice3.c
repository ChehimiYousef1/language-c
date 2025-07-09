#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// create the list node
typedef struct Node {
    char data;
    struct Node *next;
} Node;

// function to create a node and append to list
void createNode(Node** head) {
    char character;
    printf("Enter your character you want to add inside the list: ");
    scanf(" %c", &character);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = character;
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

// function to print the list
void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        printf("%c -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

//get go on the main thing idea on my typing this code
//its will to avoid the repetition of character on the list
//and print the list without repetition
//create a function supprimer Les doublons
void supprimerLesDoublons(Node** head){
    if (*head == NULL) return;
    int count[26] = {0};  // initialize
    Node *curr = *head;
    Node *prev = NULL;
    while(curr != NULL) {
        if(curr->data >= 'a' && curr->data <= 'z') {
            int index = curr->data - 'a';
            if(count[index] == 0) {
                count[index]++;
                prev = curr;
                curr = curr->next;
            }else{
                // remove duplicate safely
                prev->next = curr->next;
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
}

//you are ready to create the function to remove the duplicate character by using recursion?
//lets go....
//we need to create two function one named by supprimerHelper qui aide a suprimer and other function to remove the duplicate using supprimerHelper
void suprimerHelper(Node* curr, Node* prev, int count[]) {
    if (curr == NULL) return;

    if (curr->data >= 'a' && curr->data <= 'z') {
        int index = curr->data - 'a';

        if (count[index] == 0) {
            count[index]++;
            suprimerHelper(curr->next, curr, count);  // keep node
        } else {
            Node* temp = curr;
            if (prev != NULL) {
                prev->next = curr->next;
            }
            curr = curr->next;
            free(temp);
            suprimerHelper(curr, prev, count);  // skip duplicate
        }
    } else {
        suprimerHelper(curr->next, curr, count);  // skip non-lowercase
    }
}

void supprimerRecursion(Node** head) {
    if (*head == NULL) return;
    int count[26] = {0};
    suprimerHelper(*head, NULL, count);

    // Check if head node was a duplicate (optional based on logic)
    int index = (*head)->data - 'a';
    if (index >= 0 && index < 26 && count[index] > 1) {
        Node* old = *head;
        *head = (*head)->next;
        free(old);
    }
}

int main() {
    printf("Try programiz.pro\n");

    Node* head = NULL;

    for (int i = 0; i < 6; i++) {
        createNode(&head);  // pass address of head
    }

    printList(head);
    //supprimerLesDoublons(&head);
    supprimerRecursion(&head);
    printList(head);
    return 0;
}
