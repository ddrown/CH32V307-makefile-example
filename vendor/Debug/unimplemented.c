// unimplemented function calls that nanolib relies on
// if any of these functions are called, it'll return a failure code
// since these are weak functions, you can override these in your code base to actually do something useful

#include "reent.h"

#define __weak __attribute__((weak))

__weak int _read(int fd, char *buf, int size) {
  return -1;
}

__weak int _close(int fd) {
  return 0;
}

__weak int _fstat(int file, struct stat *st) {
  return -1;
}

__weak int _isatty(int fd) {
  return 0;
}

__weak int _lseek(int file, int offset, int whence) {
  return -1;
}
