#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("ERROR: You need at least one argument.\n");
    return 1;
  }

  int i, j;

  for (i = 1; i < argc; i++) {
    for (j = 0; argv[i][j] != '\0'; j++) {
      char letter = tolower(argv[i][j]);

      switch (letter) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        printf("%d: '%c'\n", j, toupper(letter));
        break;

      case 'y':
        if (j > 2) {
          // it's only sometimes Y
          printf("%d: '%c'\n", j, toupper(letter));
        }
        break;

      default:
        printf("%d: %c is not a vowel\n", j, toupper(letter));
      }
    }
  }

  return 0;
}
