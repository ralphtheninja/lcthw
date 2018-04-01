#include <stdio.h>
#include <string.h>
#include "dbg.h"

#define LENGTH 1000

int zeds_device(char *from, char *to, int count)
{
  int n = (count + 7) / 8;

  switch (count % 8) {
    case 0:
  again: *to++ = *from++;
    case 7:
      *to++ = *from++;
    case 6:
      *to++ = *from++;
    case 5:
      *to++ = *from++;
    case 4:
      *to++ = *from++;
    case 3:
      *to++ = *from++;
    case 2:
      *to++ = *from++;
    case 1:
      *to++ = *from++;
      if (--n > 0) {
        goto again;
      }
  }

  return count;
}

int duffs_device(char *from, char *to, int count)
{
  int n = (count + 7) / 8;

  switch (count % 8) {
  case 0:
    do {
      *to++ = *from++;
    case 7:
      *to++ = *from++;
    case 6:
      *to++ = *from++;
    case 5:
      *to++ = *from++;
    case 4:
      *to++ = *from++;
    case 3:
      *to++ = *from++;
    case 2:
      *to++ = *from++;
    case 1:
      *to++ = *from++;
    } while (--n > 0);
  }

  return count;
}

int normal_copy(char *from, char *to, int count)
{
  int i = 0;

  for (i = 0; i < count; i++) {
    to[i] = from[1];
  }

  return i;
}

int valid_copy(char *data, int count, char expects)
{
  int i = 0;
  for (i = 0; i < count; i++) {
    if (data[i] != expects) {
      log_err("[%d] %c != %c", i, data[i], expects);
      return 0;
    }
  }

  return 1;
}

int main(int argc, char **argv)
{
  char from[LENGTH] = { 'a' };
  char to[LENGTH] = { 'c' };
  int rc = 0;

  // set up the from to have some stuff
  memset(from, 'x', LENGTH);
  check(valid_copy(from, LENGTH, 'x'), "from not initialized right");

  // set it to a failure mode
  memset(to, 'y', LENGTH);
  check(valid_copy(to, LENGTH, 'y'), "to not initialized right");

  // use normal copy to
  rc = normal_copy(from, to, LENGTH);
  check(rc == LENGTH, "Normal copy failed: %d", rc);
  check(valid_copy(to, LENGTH, 'x'), "Normal copy failed");

  // reset
  memset(to, 'y', LENGTH);
  check(valid_copy(to, LENGTH, 'y'), "to not initialized right");

  // duffs version
  rc = duffs_device(from, to, LENGTH);
  check(rc == LENGTH, "Duff's device failed: %d", rc);
  check(valid_copy(to, LENGTH, 'x'), "Duff's device failed copy.");

  // reset
  memset(to, 'y', LENGTH);
  check(valid_copy(to, LENGTH, 'y'), "to not initialized right");

  // my version
  rc = zeds_device(from, to, LENGTH);
  check(rc == LENGTH, "Zed's device failed: %d", rc);
  check(valid_copy(to, LENGTH, 'x'), "Zed's device failed copy.");

  return 0;

 error:
  return -1;
}
