#include <stdio.h>

void crash()
{
  int *p = NULL;
  p[44] = 44;
}

int main()
{
  crash();
  return 0;
}
