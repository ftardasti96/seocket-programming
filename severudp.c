#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>

int main() {
  char sbuf[100];
  char *smsg;
  int len;
  //create a socket on the side of server
  int serverSockfd = socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in ServerAddr;
  struct sockaddr_in clientAdr;
  ServerAddr.sin_family = AF_INET;                                       
  ServerAddr.sin_port = htons(8081);                                   
  ServerAddr.sin_addr.s_addr = INADDR_ANY;
  bind(serverSockfd,(const struct sockaddr*)&ServerAddr,sizeof(ServerAddr));
  
  //receive what is sent to server
  recvfrom(serverSockfd,(char*)sbuf,sizeof(sbuf),0,(const struct *)&clientAdr,&len);
  printf("%s \n",sbuf);
  //printf("%d \n",clientAdr.sin_port);

  //sendto client
  // smsg = "Message from server to client";
  //sendto(serverSockfd,smsg,strlen(smsg),0,(const struct sockaddr*)&clientAdr,sizeof(clientAdr));
  
  return 0;
} 
