#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{


  int num;

  sscanf(argv[1],"%d",&num);

  if(num <= 0)
  {
    printf("%s\n", "No numbers requested!");
  }
  else
  {
    int b = 0;
    int count = 1;
    while(b<num)
    {
      if (count%2 == 0 || count% 3 == 0)
      {
        printf("%d\n", count);
        b++;
      }
      count++;
    }

  }

  return EXIT_SUCCESS;

}
