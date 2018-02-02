#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct play{
  char name[100];
  //int number;
  float numPoints; //num of points scored
  float numAss; //num of assists
  //int grad;
  float numMin; //num of minutes played
  struct play* point;
  float directOff; //defines direct offensive contribution characteristic
};
FILE *fr;
char line[80];

struct play* head;
struct play* current;



void srt(struct play* temp){
//if linkedlist is NULL, put temp as head of it
  if (head == NULL){
    head = temp;
  }


//if one other node in linked list, check to see if doc of head > doc of temp or less than to see if to put after or before
  else if(head->point == NULL){
    if(temp->directOff < head->directOff){ //if doc of temp is less than doc of head
      head->point = temp; //put temp after head in list by pointing head to temp
      //head = temp;
    }
    else if(temp->directOff > head->directOff){ //if doc of temp is greater than doc of head, replace head with temp and point temp to head
      temp->point = head; //point temp to head
      head = temp; //replace head with temp
    }

    else{
      if(strcmp(temp->name,head->name) <0){ //if doc of temp and head are equal, check to see if temp->name is alphabetically before head->name
        temp->point = head;
        head = temp; //just added this line, but replace head with temp
      }
      else{
        head->point = temp; //if head is before alphabetically and doc's are equal, keep head as head and point it to temp
      }
    }
  }

  else if (temp->directOff > head->directOff){ //if there is more than one node in list and temp->doc > head->doc, point head to temp
    struct play* nw = head; //create pointer to old head
    head = temp; //replace head with temp
    head->point = nw; //point new head (temp) to old head

  }

  else if(temp->directOff < head->directOff){ //if there is more than one node in list and temp->doc < head->doc, iterate until you know where to place it in list
    struct play* nxt = head->point; //create struct pointer variable which points to what original head is pointing to
    if (nxt == NULL){ //if there are no other nodes beyond head in list, point old head to new head (temp)
      head->point = temp;
    }
    else{


    struct play* back; //create pointer variable to set to old head
    back = head; //set back to old head
    while(temp->directOff < nxt->directOff && nxt->point != NULL){ //while temp doc is less than next node doc and next isnt null, keep iterating
      back = nxt; //push back node to next node
      nxt = nxt->point; //push next node forward
    }
    //at this point we should be at the right place to insert temp into linked list
    if(temp->directOff == nxt->directOff){ //if temp doc and nxt doc are the same, sort alphabetically
      if(strcmp(temp->name,nxt->name)<0){ //if temp name comes alphabetically before nxt name, place it before nxt and fix pointers

        back->point = temp;
        temp->point = nxt;
      }
      else{ //if temp name comes alphabetically after nxt or temp's doc is less than nxt doc then place it after nxt and fix pointers
        temp->point = nxt->point;
        nxt->point = temp;


      }

    }


    if(nxt->point == NULL && temp->directOff < nxt->directOff){ //if nxt points to NULL and temp doc is less than nxt doc then point nxt to doc
      nxt->point = temp;
    }
    else{
      back->point = temp;
      temp->point = nxt;
    }




    }

  }

  else if(temp->directOff == head->directOff){ //if temp doc equals head doc, check to see which comes first alphabetically
    if(strcmp(temp->name,head->name)<0){ //if temp comes first alphabetically, point temp to head
      temp->point = head;
    }
    else{ //if head comes first alphabetically,
      struct play* mid = head->point;
      head->point = temp;
      temp->point = mid;
    }

  }

}


int main(int argc, char *argv[])
{
  printf("hi");
  head = NULL;
  current = NULL;


  fr = fopen(argv[1],"r");//

  while(fgets(line, 65, fr) != NULL)
   {
     if (strcmp(line,"DONE\n")==0){
       break;
     }
     current = (struct play*) malloc(sizeof(struct play));
     struct play* prev = current;


     //strcpy(current->name,line);
     line[strlen(line)] = '\0';
     strcpy(current->name, line); //copies player name into player struct

/*
     char metrics[80]; //creates char array to store raw player scoring and assisting data
     char* p; //pointer to first word of saved metrics data
     strcpy(p, line); //reads in line of points and assists to p
     metrics = strtok(p, " ");//breaks down p
*/
     fgets(line,65,fr);
     char metrics[65]; //creates char array to store raw player scoring and assisting data
     char points[65];
     char assists[65];
     strcpy(metrics, line); //reads in player scoring and assisting data and stores it in metrics
     int i = 0;
     while (metrics[i] != ' ')
     {

       points[i] = metrics[i]; //puts in number of points from metrics into points
       i++;
     }
     points[i] = '\0'; //puts in end of string character into points
     int b = i++; //sets b where i left off plus 1
     int c = 0; //set variable to iterate through assists
     while (metrics[b] != '\n')
     {
       assists[c] = metrics[b]; //copy in char from metrics into assists
       b++;
       c++;
     }
     assists[c] = '\0';

     float pts = atof(points);
     float assts = atof(assists);

     //put in print files to check values of points and assists


     //fscanf(fr,"%d\n",&current->number);
     //fscanf(fr,"%d\n",&current->grad);
     current->numPoints = pts;
     current->numAss = assts;

     fgets(line,65,fr);
     char temp[65];
     strcpy(temp,line);
     temp[strlen(temp)-1] = '\0';

     float minutes = atof(temp);
     current->numMin = minutes;

     if(minutes > 0)
     {
       current->directOff = (pts+assts)/minutes;
     }
     else
     {
       current->directOff = 0.0;
     }
/*
     printf("%s",current->name);
     printf("%f",current->numPoints);
     printf("%f",current->numAss);
     printf("%f",current->numMin);
     printf("%f",current->directOff);

*/




     srt(current);

   }

   current = head;
   while(current != NULL)
   {
     char *foo = current->name;
     foo[strlen(foo) - 1] = 0;
     printf("%s ", foo);
     printf("%f\n",current->directOff);
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
