#include <stdio.h>

/* This is a comment. */
int main(int argc, char *argv[])
{
  int distance = 100;

  // this is also a comment
  printf("You are %d miles away.\n", distance);
  printf("Number of arguments: %d\n", argc);

  for (int i = 0; i < argc; ++i) {
    printf("Argument: %d, Value: %s\n", i+1, argv[i]);
  }

  return 0;
}
