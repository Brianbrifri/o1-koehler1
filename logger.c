#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"

typedef struct list_struct {
  data_t item;
  struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

char * addMsg(data_t data) {
  log_t *newEntry;
  int entrySize;

  entrySize = sizeof(log_t) + strlen(data.string) + 1;
  //Couldn't add newEntry
  if((newEntry = (log_t *) (malloc(entrySize))) == NULL) {
    perror("Error:");
    return "Could not malloc for log\n";
  }

  newEntry->item.time = data.time;
  newEntry->item.string = (char *)newEntry + sizeof(log_t);
  strcpy(newEntry->item.string, data.string);
  newEntry->next = NULL;

  if(headptr == NULL) {
    headptr = newEntry;
  }
  else {
    tailptr->next = newEntry;
  }
  tailptr = newEntry;

  return "Successfully added data to log\n";
}

void clearLog(void) {
  log_t *nodeptr;
  log_t *next;

  nodeptr = headptr;
  next = headptr->next;
  if(!nodeptr) {
    return;
  }
  while(nodeptr) {
    free(nodeptr->item.string);
    free(nodeptr);
    nodeptr = next;
    next = nodeptr->next;
  }

}

char *getLog(void) {
  log_t *nodeptr;
  size_t nodeSize;
  char *logString;

  nodeSize = 20;
  nodeptr = headptr;

  if(!nodeptr) {
    return "No errors t'day, mate!\n";
  }

  while(nodeptr) {
    nodeSize += (sizeof(nodeptr) + sizeof(nodeptr->item.string) + 4);
    nodeptr = nodeptr->next;
  }

  logString = malloc(nodeSize);
  if(!logString) {
    perror("Error: ");
    return "Unable to allocate memory for string\n";
  }
  logString = "*****Begin Log*****\n";
  nodeptr = headptr;
  while(nodeptr) {
    //strcat(logString, asctime(localtime(nodeptr->item.time)));
    strcat(logString, nodeptr->item.string);
    strcat(logString, "\n");
    nodeptr = nodeptr->next;
  }
  return logString;
}

char * saveLog(char *filename) {
  char *logString;
  logString = getLog();
  FILE *file = fopen(fileName, "a");
  if(!file) {
    perror("Error:");
    return("Could not open file\n");
  }
  else {
    fprintf(file, logString);
    fclose(file); 
  }
  free(logString);
  return "Successfully saved log\n";
}

void printHelpMessage(void) {
    printf("\nThank you for using the help menu!\n");
    printf("The following is a helpful guide to enable you to use this\n");
    printf("debugger program to the best of your ability!\n\n");
    printf("-h, -help: Prints this help message.\n");
    printf("-n: Allows you to set the number of messages to the alien planet Krudo.\n");
    printf("\tThe default value is 42.\n");
    printf("-l: Allows you to set the filename for the logger so the aliens can see how bad you mess up.\n");
}
