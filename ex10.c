#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("ERROR: You need one argument.\n");
    return 1;
  }

  int i;

  for (i = 0; argv[1][i] != '\0'; i++) {
    char letter = tolower(argv[1][i]);

    switch (letter) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      printf("%d: '%c'\n", i, toupper(letter));
      break;

    case 'y':
      if (i > 2) {
        // it's only sometimes Y
        printf("%d: '%c'\n", i, toupper(letter));
      }
      break;

    default:
      printf("%d: %c is not a vowel\n", i, toupper(letter));
    }
  }

  return 0;
}
