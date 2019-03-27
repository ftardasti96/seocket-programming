#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main() {
  char buf[1000];
  char *ermsg = "404 error page not found";
  socklen_t len;
  //create a socket on the side of server
  int serverSockfd = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in ServerAddr;
  struct sockaddr_storage connectionSock;
  ServerAddr.sin_family = AF_INET;                                       
  ServerAddr.sin_port = htons(8081);
  struct in_addr addr;
  inet_aton("127.1.2.3",&addr);
  ServerAddr.sin_addr = addr;

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
  recv(newfd,buf,sizeof(buf),0);
  printf("%s \n",buf);

  //pars request that is sent in buf
  int test1 = 0;
  for(test1;;test1++)
    if(buf[test1]==47)
      break;

  int test2 = test1;
  for(test2;;test2++)
    if(buf[test2]==32)
      break;

  char req[20]={0};
  for(int k=test1;k<test2;k++)
    req[k-test1] = buf[k];
  printf("%s\n",req);
  
  //send html file to client
  char header[] = "HTTP/1.0 200 OK\r\n";
  char html[]="<html><head> WEBSERVER  </head><body><pre>!!!!!Hello World!!!!!!</pre></body></html>";
  
  char data[2048]={0};
  snprintf(data,sizeof(data),"%s %s",header,html);
  if(memcmp(req,"/helloworld.html",17)==0)
      send(newfd,data,strlen(data),0);
  else
    send(newfd,(const char*)ermsg,strlen(ermsg),0);

  return 0;
} 
