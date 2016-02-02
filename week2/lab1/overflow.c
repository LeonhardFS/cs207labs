// overflow.c
#include <stdlib.h>
#include <stdio.h>

void win()
{
  printf("Success!\n");
  exit(0);
}

int victim_function(int index)
{
  int64_t a[5] = {1,2,3,4,5};
  a[index] = (int64_t)(&win);
  return 0;
}

int main(int argc, char **argv)
{
  int magic_number = 0;

  if( argc>1 ) {
    magic_number = atoi(argv[1]);
  } else {
    printf("Please enter a magic number.\n");
    return -1;
  }

  victim_function( magic_number );

  return 0;
}