#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *next;
} node_t;

// Push a new value onto the end of the linked list.
void push(node_t *head, int val) {
  node_t *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(node_t));
  current->next->val = val;
  current->next->next = NULL;
}

// Add a new value at the specified index.
void add(node_t **head, int idx, int val) {
  if (idx == 0) {
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
  }

  node_t *current = *head;
  int i = 0;

  do {
    if (i == idx - 1) {
      node_t *next = current->next;
      current->next = malloc(sizeof(node_t));
      current->next->val = val;
      current->next->next = next;
      return;
    }

    current = current->next;
    i++;
  } while (current->next != NULL);

}

// Print the list.
void printeach(node_t *head) {
  node_t *current = head;
  while (current->next != NULL) {
    printf("l: %d\n", current->val);
    current = current->next;
  }
}

// Create a new list.
node_t *new() {
  node_t *head = NULL;

  head = malloc(sizeof(node_t));
  head->val = 1;
  head->next = NULL;

  return head;
}

int main() {
  node_t *head = new();

  push(head, 10);
  push(head, 20);
  push(head, 30);

  add(&head, 1, 40);

  printeach(head);

  return 0;
}
