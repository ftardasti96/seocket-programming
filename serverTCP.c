#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>

int main() {
  char sbuf[100];
  socklen_t len;
  //create a socket on the side of server
  int serverSockfd = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in ServerAddr;
  struct sockaddr_storage connectionSock;
  ServerAddr.sin_family = AF_INET;                                       
  ServerAddr.sin_port = htons(8081);                                   
  ServerAddr.sin_addr.s_addr = INADDR_ANY;

  //bind server address to socket
  bind(serverSockfd,(const struct sockaddr*)&ServerAddr,sizeof(ServerAddr));
  //listenon port for msg from client
  if(listen(serverSockfd,50) == -1)
    printf("listen problem");

  //accept
  //creats a new file descriptor as a connection, not socket
  //to send and receive msgs
  len = sizeof(struct sockaddr_storage);
  int newfd = accept(serverSockfd,(struct sockaddr*)&connectionSock,&len);
    if(newfd<0)
    printf("accept problem");

  //receive from client
  recv(newfd,sbuf,sizeof(sbuf),0);
  printf("client sent: %s \n",sbuf);

  //send to client
  char* msg = "Hello world!";
  send(newfd,(const char*)msg,strlen(msg),0);
  
  return 0;
} 
