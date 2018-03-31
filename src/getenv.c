#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  if (argc == 1) {
    printf("Need one argument\n");
    exit(1);
  }

  char *name = argv[1];
  char *s = getenv(name);

  if (s == NULL) {
    printf("Missing environment variable: %s\n", name);
    exit(1);
  } else {
    printf("%s\n", s);
  }

  return 0;
}
