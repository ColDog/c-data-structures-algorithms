#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *left;
  struct node *right;
} node_t;

void destroy_tree(node_t *leaf) {
  if (leaf != 0) {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    free(leaf);
  }
}

void insert(node_t **leaf, int val) {
  if (*leaf == 0) {
    *leaf = malloc(sizeof(node_t));
    (*leaf)->val = val;
    (*leaf)->left = 0;
    (*leaf)->right = 0;
  } else if (val < (*leaf)->val) {
    insert(&(*leaf)->left, val);
  } else if (val > (*leaf)->val) {
    insert(&(*leaf)->right, val);
  }
}

node_t *search(node_t *leaf, int val) {
  if (leaf == 0) {
    return 0;
  }

  if (leaf->val == val) {
    return leaf;
  } else if (leaf->val > val) {
    return search(leaf->left, val);
  } else if (leaf->val < val) {
    return search(leaf->right, val);
  }

  return 0;
}

int main() {
  node_t *root = 0;

  insert(&root, 10);
  insert(&root, 20);
  insert(&root, 30);

  printf("search 30 %d\n", search(root, 30)->val);

  return 0;
}
