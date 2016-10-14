#include <stdio.h>
#include <stdlib.h>

int last_id = 0;

typedef struct node {
  int id;
  int distance;
  struct edge *first_edge;
} node_t;

typedef struct edge {
  int weight;
  int target_id;
  struct edge *next;
  struct edge *prev;
} edge_t;

node_t *new_node() {
  node_t *node = NULL;
  node = malloc(sizeof(node_t));
  node->id = last_id++;
  node->distance = 0;
  node->first_edge = NULL;

  return node;
}

void add_edge(node_t *node, node_t *target, int weight) {
  edge_t *edge = NULL;
  edge = malloc(sizeof(edge_t));
  edge->weight = weight;
  edge->target_id = target->id;
  edge->next = NULL;
  edge->prev = NULL;

  if (node->first_edge == NULL) {
    node->first_edge = edge;
  } else {
    edge_t *current = node->first_edge;
    while (current->next != NULL) {
      current = current->next;
    }

    edge->prev = current;
    current->next = edge;
  }
}

void print_graph(node_t *graph[20]) {
  for (int i = 0; i < 20; i++) {
    printf("[%d] -> ", graph[i]->id);

    edge_t *current = graph[i]->first_edge;
    if (current == NULL) {
      printf("(none)\n");
    } else {
      printf("%d ", current->target_id);
      while(current->next != NULL) {
        printf("%d ", current->target_id);
        current = current->next;
      }
      printf("\n");
    }
  }
}

node_t * graph[20];

int main() {
  for (int i = 0; i < 20; i++) {
    graph[i] = new_node();
    if (i != 0) {
      add_edge(graph[i], graph[i-1], 0);
    }
    if (i > 4) {
      add_edge(graph[i], graph[i-2], 3);
      add_edge(graph[i], graph[i-3], 3);
      add_edge(graph[i], graph[i-4], 3);
    }
  }

  print_graph(graph);
  return 0;
}
