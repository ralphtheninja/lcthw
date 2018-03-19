#include <stdio.h>  // for printf()
#include <assert.h> // for assert()
#include <stdlib.h> // for malloc() and free()
#include <string.h> // for strdup()

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

/**
 * Constructor for Person
 */
struct Person*
Person_create(char *name, int age, int height, int weight)
{
  struct Person *who = malloc(sizeof (struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

/**
 * Destructor for Person
 */
void Person_destroy(struct Person* who)
{
  assert(who != NULL);

  free(who->name);
  free(who);
}

/**
 *
 */
void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

/**
 *
 */
void Person_print2(struct Person who)
{
  printf("Name: %s\n", who.name);
  printf("\tAge: %d\n", who.age);
  printf("\tHeight: %d\n", who.height);
  printf("\tWeight: %d\n", who.weight);
}

/**
 *
 */
int main(int argc, char *argv[])
{
  printf("sizeof (struct Person): %ld\n", sizeof (struct Person));

  struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
  printf("Joe is at memory location: %p\n", joe);
  Person_print(joe);

  struct Person *frank = Person_create("Frank Blank", 20, 72, 180);
  printf("Frank is at memory location: %p\n", frank);
  Person_print(frank);

  struct Person stack = { "Mr Stack Struct", 88, 99, 314 };
  printf("Stack is at memory location: %p\n", &stack);
  Person_print(&stack);
  Person_print2(stack);

  // make everyone age 20 years and print them again
  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}
