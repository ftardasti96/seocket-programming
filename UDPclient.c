#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
  char *buf = "Message";
  char *msg;
  //creat client socket 
  int clientSockfd = socket(AF_INET,SOCK_DGRAM,0);
  //the server address we want to send 
  struct sockaddr_in ServerAddr;
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port = htons(8081);
  ServerAddr.sin_addr.s_addr = INADDR_ANY;

  sendto(clientSockfd,(const char*)buf,strlen(buf),MSG_CONFIRM,(const struct sockaddr*)&ServerAddr,sizeof(ServerAddr));

  //what is received from server?
  //  recv(clientSockfd,msg,sizeof(msg),0);
  //printf("server sent %s \n",msg);

  //close socket
  close(clientSockfd);
  return 0;
  
}
