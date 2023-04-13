#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(){
 
  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;
  int flag=1;
 
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");
 
  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5566);
  server_addr.sin_addr.s_addr = INADDR_ANY;
 
  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", 5566);
 
  listen(server_sock, 5);
  printf("Listening...\n");
 
  
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");
 while(flag==1)
 {
    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
    
        if (strcmp(buffer, "exit") == 0)
{
    
    break;
}
    
    printf("Client: %s\n", buffer);
 
    bzero(buffer, 1024);
    printf("Enter the message to send: \n");
    scanf("%s", buffer);
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);
    
 }
  
    close(server_sock);
    close(client_sock);
    printf("[+]Client disconnected.\n\n");
    return 0;
}


