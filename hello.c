#include "stdio.h"

#include "add.h"

int main()
{

  int a = 1;
  int b = 2;

  float c = 0.5;

  printf("Hello World! a=%d b=%d, c=%f\n", a, b, c);

  int d = add_two_ints(a, b);
  printf("d = %d\n", d);

  return 0;
}
