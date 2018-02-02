#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct play{
  char name[100];
  struct play* point;
  float directOff; //defines direct offensive contribution characteristic
};

void printPlay(struct play* head){
  printf("%s %f\n",head->name, head->directOff);
}
int comparator(struct play* one, struct play* two){
  if(one->directOff>two->directOff){
    return 1;
  }
  else if(one->directOff<two->directOff){
    return -1;
  }
  else if(strcmp(one,two)>0){
    return -1;
  }
  else{
    return 1;
  }
}

struct play* addToList(struct play* head, struct play* newPlay){
  if(comparator(head,newPlay)<0){
      newPlay->point = head;
      return newPlay;
  }
  struct play* holder = head;
  while(holder->point!=NULL){
    if(comparator(holder->point,newPlay)<0){
      newPlay->point = holder->point;
      holder->point =newPlay;
      return head;
    }
    holder = holder->point;
  }
  holder->point = newPlay;
  return head;
}

void printList(struct play* head){
  struct play* holder = head;
  while(holder!=NULL){
    printPlay(holder);
    holder=holder->point;
  }
}


int main(int argc, char *argv[])
{
  FILE *fr;
  char line[80];
  struct play* head = NULL;

  fr = fopen(argv[1],"r");//
  if(fgets(line,65,fr)&&line[0]!='\0'){
    head = (struct play*) malloc(sizeof(struct play));
    *head = (struct play){
      .name = NULL,
      .point = NULL,
      .directOff = 0
    };
    strcpy(head->name, line);
    head->name[strlen(head->name)-1]='\0';
    fgets(line,65,fr);
    char pointsStr[65];
    char assistsStr[65];
    char minutesStr[65];
    int count = 0;
    int index = 0;
    strcpy(pointsStr,line);
    while(line[count]!=' '){
      count++;
    }
    pointsStr[count] = '\0';
    count++;
    while(line[count]!='\n'){
      assistsStr[index]=line[count];
      count++;
      index++;
    }
    fgets(line,65,fr);
    strcpy(minutesStr, line);
    minutesStr[strlen(minutesStr)-1]='\0';

    float points = atof(pointsStr);
    float assists = atof(assistsStr);
    float minutes = atof(minutesStr);
    float dOff = minutes == 0 ? 0 : (points+assists)/minutes;
    head->directOff = dOff;
  }
  else{
    printf("PLAYER FILE IS EMPTY");
    fclose(fr);
  }
  fgets(line,65,fr);

  while(strcmp(line,"DONE\n")!=0 && strcmp(line,"DONE")!=0){
    struct play* newPlay = (struct play*) malloc(sizeof(struct play));
    *newPlay = (struct play){
      .name = NULL,
      .point = NULL,
      .directOff = 0
    };
    strcpy(newPlay->name, line);
    newPlay->name[strlen(newPlay->name)-1]='\0';
    fgets(line,65,fr);
    char pointsStr[65];
    char assistsStr[65];
    char minutesStr[65];

    int count = 0;
    int index = 0;
    strcpy(pointsStr,line);
    /*
    while(line[count]!=' '){
      count++;
    }
    pointsStr[count] = '\0';
    count++;
    while(line[count]!='\n'){
      assistsStr[index]=line[count];
      count++;
      index++;
    }*/
    char* pch = strtok(line," \n");
    strcpy(pointsStr,pch);
    pch = strtok (NULL, " \n");
    strcpy(assistsStr,pch);
    fgets(line,65,fr);
    strcpy(minutesStr, line);
    minutesStr[strlen(minutesStr)-1]='\0';

    float points = atof(pointsStr);
    float assists = atof(assistsStr);
    float minutes = atof(minutesStr);
    float dOff = minutes == 0 ? 0 : (points+assists)/minutes;
    newPlay->directOff = dOff;
    head = addToList(head,newPlay);
    //printPlay(newPlay);
  //  head = addToList(head,newPlay);
    fgets(line,65,fr);
  }
   printList(head);
   fclose(fr);
   exit(0);
 }
