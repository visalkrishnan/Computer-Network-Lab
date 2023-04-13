#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
 
  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;
  int flag=1;
 
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");
 
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(5566);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
  while(flag==1)
  {
  bzero(buffer, 1024);
  printf("Enter the message to send: ");
  scanf("%s", buffer);
  
  printf("Client: %s\n", buffer);
  send(sock, buffer, strlen(buffer), 0);
   if (strcmp(buffer, "exit") == 0)
{
    close(sock);
    break;
}
  
  
  bzero(buffer, 1024);
  recv(sock, buffer, sizeof(buffer), 0);
  printf("Server: %s\n", buffer);
 
 }
  
  printf("Disconnected from the server.\n");
 
  return 0;
}

