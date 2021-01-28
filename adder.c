#include "csapp.h"

int main(void){
  char *buf, *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  char num1[10], num2[10];
  int n1 = 0, n2 = 0;

  if ((buf = getenv("QUERY_STRING")) != NULL){
    p = strchr(buf, '&');
    *p = '\0';
    strcpy(arg1, buf);
    strcpy(arg2, p+1);
    
    p = strchr(arg1, '=');
    strcpy(num1, p+1);
    p = strchr(arg2, '=');
    strcpy(num2, p+1);
    n1 = atoi(num1);
    n2 = atoi(num2);
  }

  sprintf(content, "QUERY_STRING=%s\n", buf);
  sprintf(content, "%s %d + %d = %d\r\n",content, n1, n2, n1+n2);

  printf("Connection: close\r\n");
  //printf("Content-length: %d\r\n", (int)strlen(content));
  printf("\r\n");

  printf("%s", content);
  printf("\r\n");
  printf("%s", content);
  printf("awefawef");

  fflush(stdout);
  exit(0);
}