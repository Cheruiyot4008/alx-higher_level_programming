#include <stdio.h>
#include <stdlib.h>

typedef struct listint {
    int n;
    struct listint *next;
} listint_t;

int is_palindrome(listint_t **head) {
    if (*head == NULL || (*head)->next == NULL)
        return 1;

    listint_t *slow = *head, *fast = *head, *prev_slow = *head, *second_half;
    int is_palindrome = 1;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;

        listint_t *next = slow->next;
        slow->next = prev_slow;
        prev_slow = slow;
        slow = next;
    }

    if (fast != NULL)
        slow = slow->next;

    second_half = slow;
    while (prev_slow != NULL && second_half != NULL) {
        if (prev_slow->n != second_half->n) {
            is_palindrome = 0;
            break;
        }
        prev_slow = prev_slow->next;
        second_half = second_half->next;
    }

    slow = NULL;
    while (prev_slow != NULL) {
        listint_t *next = prev_slow->next;
        prev_slow->next = slow;
        slow = prev_slow;
        prev_slow = next;
    }
    *head = slow;

    return is_palindrome;
}

int main(void) {
    listint_t *head = NULL;

    for (int i = 1; i <= 3; i++) {
        listint_t *new_node = malloc(sizeof(listint_t));
        if (new_node == NULL) {
            perror("Memory allocation error");
            return EXIT_FAILURE;
        }
        new_node->n = i;
        new_node->next = head;
        head = new_node;
    }
    for (int i = 3; i >= 1; i--) {
        listint_t *new_node = malloc(sizeof(listint_t));
        if (new_node == NULL) {
            perror("Memory allocation error");
            return EXIT_FAILURE;
        }
        new_node->n = i;
        new_node->next = head;
        head = new_node;
    }

    if (is_palindrome(&head))
        printf("The list is a palindrome\n");
    else
        printf("The list is not a palindrome\n");

    listint_t *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}
