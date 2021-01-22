/*tiny.c - A simple, iterative HTTP/1.0 Web server that uses
    Get method to serve static and dynamic content
*/
#include "csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int  parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);



int main(int argc, char **argv)
{
  int listenfd, connfd;
  char hostname[MAXLINE], port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  /*
  ./client 127.0.0.1 9190
  argc는 3이 되고,
  *argv[0]는 “./client” 문자열을 가리키고,
  *argv[1]는 “127.0.0.1” 문자열을 가리키고,
  *argv[2]는 “9190” 문자열을 가리킨다.
  */
  //check command-line args
  if (argc != 2){
    fprintf(stderr, "usage: %s <port>\n",argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);
  while(1){
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    GETnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
    printf("Accepted connection from (%s, %s)\n", hostname, port);
    doit(connfd);
    Close(connfd);
  }
}
