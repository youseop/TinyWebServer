# include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv){
  int listenfd, connfd;
  socklen_t clientlen;

  //모든 형태의 소켓주소를 주소를 저장하기에 충분히 크다.
  ///그래서 코드의 프로토콜을 독립적으로 유지시킬 수 있다.
  //911p아랫부분
  //서버 입장에서는 어떤 클라이언트가 들어올지 모른다!
  struct sockaddr_storage clientaddr;//왜 애초에 포인터 변수로 선언하지 않았을까?
  char client_hostname[MAXLINE], client_port[MAXLINE];

  if(argc != 2){
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  //listen중인 sockt, file descripter
  listenfd = Open_listenfd(argv[1]);

  while(1){
    clientlen = sizeof(struct sockaddr_storage);

    //서버는 accept함수를 호출해서 클라이언트로부터의 연결 요청을 기다린다. 901p
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    //host, port 받아온다.
    //clientaddr ??!
    Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
    printf("Connected to (%s, %s)\n", client_hostname, client_port);
    echo(connfd);
    Close(connfd);
  }
  exit(0);
}

void echo(int connfd){
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);
  //eof를 만날 때 까지 반복적으로 읽고 써줌!
  while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
    printf("server received %d bytes\n", (int)n);
    Rio_writen(connfd, buf, n);
  }
}