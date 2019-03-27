#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
  char *buf = "Message from client sent to server";
  char msg[100];
  //creat client socket 
  int clientSockfd = socket(AF_INET,SOCK_STREAM,0);
  //the server address we want to send 
  struct sockaddr_in ServerAddr;
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port = htons(8081);
  ServerAddr.sin_addr.s_addr = INADDR_ANY;

  //create tcp connection
  connect(clientSockfd,(const struct sockaddr*)&ServerAddr,sizeof(ServerAddr));

  //send to server
  send(clientSockfd,(const char*)buf,strlen(buf),0);

  //receive from server
  recv(clientSockfd,msg,sizeof(msg),0);
  printf("server sent: %s \n",msg);
  
  //close socket
  close(clientSockfd);
  return 0;
  
}
