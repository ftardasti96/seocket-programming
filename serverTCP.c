#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>

char* parser(char* buf)
{
  char *req;
  for(int i = 0 ; i < sizeof(buf); i++)
    {
      if(buf[i] == 47)
	for(int j = 0; buf[i] != 32; j++)
	  req[j] = buf[i];
    }

  return req;

}


int main() {
  char buf[1000];
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
  //  printf("%d %d\n",test1,test2);
  printf("%s\n",req);
  
  //send to client
  char* msg = "Hello world!";
  //if(req == "/helloworld.html")
  send(newfd,(const char*)msg,strlen(msg),0);
  //  send(newfd,hello.html,sizeof(hello.html),0);
  return 0;
} 
