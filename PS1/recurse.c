#include <stdio.h>
#include <stdlib.h>


int rc(int n){

  if (n==0){
    return 2;
  }
  else if (n==1){
    return 3;
  }
  else{
    return 3*rc(n-2)+rc(n-1)+1;
  }


}

//#assume that argument is in $a0 and that return value after function call is in $v0
//#call function with jal which jumps to function and saves current address of where you are in (which line) $ra and after function is done goes back to $ra
//#jr is like return
//#at end of regular function you can do jr but now you don't know how many times it is being recursed
#


int main(int argc, char *argv[])
{
  int num;

  sscanf(argv[1],"%d",&num);
  if (num == 0){
    printf("%d\n", 2);
  }
  else if(num < 0){
    printf("%s\n", "Invalid input!");
  }

  else{
    printf("%d\n", rc(num));
  }

}
