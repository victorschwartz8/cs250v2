#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct play{
  char name[100];
  int number;
  int grad;
  struct play* point;
};
FILE *fr;
char line[80];

struct play* head;
struct play* current;



void srt(struct play* temp){

  if (head == NULL){
    head = temp;
  }

  else if(head->point == NULL){
    if(temp->grad < head->grad){
      temp->point = head;
      head = temp;
    }
    else if(temp->grad > head->grad){
      head->point = temp;
    }

    else{
      if(strcmp(temp->name,head->name) <0){
        temp->point = head;
      }
      else{
        head->point = temp;
      }
    }
  }

  else if (temp->grad < head->grad){
    struct play* nw = head;
    head = temp;
    head->point = nw;
  }

  else if(temp->grad > head->grad){
    struct play* nxt = head->point;
    if (nxt == NULL){
      head->point = temp;
    }
    else{


    struct play* back;
    back = head;
    while(temp->grad > nxt->grad && nxt->point != NULL){
      back = nxt;
      nxt = nxt->point;
    }

    if(temp->grad == nxt->grad){
      if(strcmp(temp->name,nxt->name)<0){

        back->point = temp;
        temp->point = nxt;
      }
      else{
        temp->point = nxt->point;
        nxt->point = temp;


      }

    }


    if(nxt->point == NULL && temp->grad > nxt->grad){
      nxt->point = temp;
    }
    else{
      back->point = temp;
      temp->point = nxt;
    }




    }

  }

  else if(temp->grad == head->grad){
    if(strcmp(temp->name,head->name)<0){
      temp->point = head;
    }
    else{
      struct play* mid = head->point;
      head->point = temp;
      temp->point = mid;
    }

  }

}



int main(int argc, char *argv[])
{
  head = NULL;
  current = NULL;


  fr = fopen(argv[1],"r");//

  while(fgets(line, 80, fr) != NULL)
   {
     if (strcmp(line,"DONE\n")==0){
       break;
     }
     current = (struct play*) malloc(sizeof(struct play));
     struct play* prev = current;


     strcpy(current->name,line);
     fscanf(fr,"%d\n",&current->number);
     fscanf(fr,"%d\n",&current->grad);


     srt(current);

   }
   current = head;
   while(current != NULL)
   {
     char *foo = current->name;
     foo[strlen(foo) - 1] = 0;
     printf("%s ", foo);
     printf("%d\n",current->number);
     current = current->point;

   }

   while(head != NULL){
     struct play* t;
     t = head;
     head = head ->point;
     free(t);
   }
   fclose(fr);
   return 0;

}
