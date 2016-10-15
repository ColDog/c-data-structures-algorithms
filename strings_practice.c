#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char key_t[255];

key_t *from(key_t *cur, int from) {
  key_t *dest = malloc(sizeof(key_t));
  memcpy(dest, *cur + from, strlen(*cur));
  return dest;
}

key_t *up_to(key_t *cur, int up_to) {
  key_t *dest = malloc(sizeof(key_t));
  memcpy(dest, *cur, up_to + 1);
  return dest;
}

int main() {
  key_t x = "abcdefg";

  key_t *y = from(&x, 4);

  char *test = "test";
  key_t *dest = malloc(sizeof(key_t));
  strncpy(*dest, test, strlen(test));

  printf("%s\n", *dest);

  return 0;
}
