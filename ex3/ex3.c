#include <stdio.h>

int main()
{
  int age = 10;
  int height = 72;
  double pi = 3.14154;

  printf("I am %d years old.\n", age);
  printf("I am %d inches tall.\n", height);
  printf("Let's try a beep \a \n");
  printf("What about backspace\b\b\bDUDE\n");
  printf("Printing pi %10.3f\n", pi);
  printf("Printing pi 2 %.4f\n", pi);

  return 0;
}
