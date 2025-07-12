void partition(Node* Head) {
    int number;
    printf("Enter the number you want to search for: ");
    scanf("%d", &number);

    if (Head == NULL) return;

    Node *Current = Head;
    Node *prev = NULL;
    Node *next = NULL;
    int found = 0;

    while (Current != NULL) {
        if (Current->data == number) {
            found = 1;

            if (Current->next != NULL && Current->next->data < Current->data) {
                next = Current->next;
                Current->next = next->next;
                next->next = Current;

                if (prev == NULL)
                    Head = next;
                else
                    prev->next = next;

                prev = next;
            } else {
                prev = Current;
                Current = Current->next;
            }
        } else {
            prev = Current;
            Current = Current->next;
        }
    }

    if (found == 0)
        printf("We can't find\n");

    return;
}
