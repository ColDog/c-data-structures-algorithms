#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Key types
typedef char key_t[255];

key_t *from(key_t *cur, int from) {
  key_t *dest = malloc(sizeof(key_t));
  memcpy(dest, *cur + from, strlen(*cur));
  return dest;
}

key_t *up_to(key_t *cur, int up_to) {
  key_t *dest = malloc(sizeof(key_t));
  memcpy(dest, *cur, up_to);
  return dest;
}

// Implements a radix tree
// Radix tree splits a string and separates it into common parts
typedef struct node {
  key_t *part;
  struct node *first_child;
  struct node *next_sibling;
} node_t;

node_t *new(key_t *part) {
  node_t *node = NULL;
  node = malloc(sizeof(node_t));
  node->part = part;
  node->first_child = NULL;
  node->next_sibling = NULL;

  // printf("new: %s\n", *part);
  return node;
}

node_t *snew(char *s) {
  key_t *dest = malloc(sizeof(key_t));
  strncpy(*dest, s, strlen(s));
  return new(dest);
}

void insert(node_t **root, key_t *val) {
  node_t *node = *root;

  int i;

  for (i = 0; i < strlen(*node->part); i++) {
    if ((*val)[i] != (*node->part)[i]) {

      // Split the node into two parts depending on the incoming
      // values. The original node takes over as the

      // create a 'next_node' which takes over this nodes children.
      node_t *next_node = new(from(node->part, i));
      next_node->first_child = node->first_child;
      node->first_child = next_node;

      // create a new sibling.
      node_t *new_sibling = new(from(val, i));
      next_node->next_sibling = new_sibling;

      // original node takes a new name.
      node->part = up_to(val, i);

      return;
    }
  }

  // the piece after where we've gotten too.
  key_t *next_part = from(val, i);

  // We reached the end, that means everything matches with this insert so far.
  if (node->first_child == NULL) {
    // this node doesn't have any children yet! we can add ourselves as the first.
    node->first_child = new(next_part);
    return;
  }

  node_t *cur;

  if (strlen(*next_part) == 0) {
    // hey we made it!, make sure we add an empty leaf node here to mark that
    // this key exists.
    cur = node->first_child;
    while (cur->next_sibling != NULL) {
      cur = cur->next_sibling;
    }
    cur->next_sibling = new(next_part);
    return;
  }

  cur = node->first_child;
  while (cur != NULL) {
    // we see if we can even go down the path with the sibling.
    if (strlen(*cur->part) > 0 && (*next_part)[0] == (*cur->part)[0]) {
      // we found a sibling to continue on with!
      // insert will walk through this sibling and either split it or find a
      // child to add it to.
      return insert(&cur, next_part);
    }
    cur = cur->next_sibling;
  }

  // No siblings start with what this starts with, so, lets create the sibling!
  // Note, since we reached the end 'cur' should be the last sibling.
  cur->next_sibling = new(next_part);
}

void sinsert(node_t **root, char *sval) {
  key_t *dest = malloc(sizeof(key_t));
  strncpy(*dest, sval, strlen(sval));
  return insert(root, dest);
}

node_t *find(node_t *root, char *sval) {
  node_t *node = root;
  int idx = 0;
  int nidx = 0;
  int depth = 1;

  while (node != NULL) {
    if (strlen(sval) == idx) {

      node_t *cur = node->first_child;
      if (cur == NULL) {
        // leaf node return true
        return node;
      }

      while (cur != NULL) {
        if (strlen(*cur->part) == 0) {
          return node;
        }
        cur = cur->next_sibling;
      }

      return NULL;
    }

    if (sval[idx] == (*node->part)[nidx]) {
      idx++;
      nidx++;
      continue;
    }

    if (node->next_sibling == NULL) {
      node = node->first_child;
    } else {
      node = node->next_sibling;
    }
    depth++;
    nidx = 0;
  }
  return NULL;
}

void can_find(node_t *root, char *sval) {
  node_t *res = find(root, sval);
  if (res == NULL) {
    printf("ERR cannot find: %s\n", sval);
  } else {
    printf("found: %s at %s\n", sval, *res->part);
  }
}

void print_tree(node_t *root) {
  node_t *cur = root->first_child;
  printf("\n");
  printf("%s\n", *root->part);
  while(cur != NULL) {
    printf("| %s |", *cur->part);
    cur = cur->next_sibling;
  }
  printf("\n");

  cur = root->first_child;
  while(cur != NULL) {
    if (cur->first_child != NULL) {
      print_tree(cur);
    }
    cur = cur->next_sibling;
  }
}


// inserts into the tree example
// (milk)
// > insert mill
//  (mil)
//  |   |
// (k) (l)
// > insert mix
//  (mi)
//  |  |
// (x)(l)
//    | |
//   (k)(l)
// > insert mile
//  (mi)
//  |  |
// (x)(l)____
//    |  |  |
//   (k)(l)(e)
int main() {
  node_t *n = snew("test");
  node_t **root = &n;

  sinsert(root, "teapot");
  sinsert(root, "tea");

  print_tree(*root);

  can_find(*root, "test");

  return 0;
}
