int nstrlen(char *s) {
  s = s - sizeof(int32_t);
  return *((int32_t *)s);
}
