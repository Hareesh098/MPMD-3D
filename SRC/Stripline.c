#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *Stripline(FILE *input, char *BUF){
  const int SLEN = 256;
  char STR[SLEN];
  fgets(STR,SLEN,input);
  char *PCH;
  PCH=strchr(STR,'#');
  if(PCH==0){
    printf("SOMETHING IS WRONG WITH THE INPUT FILE\n");
    exit(1);
  }
  strncpy(BUF, STR, PCH-STR+1);
  return (BUF);
}
