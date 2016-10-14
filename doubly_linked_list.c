#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
  struct node *prev;
} node_t;

node_t * insert(node_t *leaf, int data) {
  if (leaf == NULL) {
    leaf = malloc(sizeof(node_t));
    leaf->prev = NULL;
    leaf->next = NULL;
    leaf->data = data;
  }

  node_t *next = NULL;

  next = malloc(sizeof(node_t));
  next->prev = leaf;
  next->next = leaf->next;
  next->data = data;

  return next;
}

void print_forward(node_t *root) {
  node_t *current = root;
  while (current->next != NULL) {
    printf("> %d\n", current->data);
    current = current->next;
  }
}

void print_reverse(node_t *root) {
  node_t *current = root;
  while (current->prev != NULL) {
    printf("> %d\n", current->data);
    current = current->prev;
  }
}


int main() {
  node_t *root = insert(NULL, 0);

  root = insert(root, 10);
  root = insert(root, 10);
  root = insert(root, 10);

  print_reverse(root);

  return 0;
}
