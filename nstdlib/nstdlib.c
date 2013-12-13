#include <stdint.h>

int32_t nstrlen(char *s) {
  s = s - sizeof(int32_t);
  return *((int32_t *)s);
}
