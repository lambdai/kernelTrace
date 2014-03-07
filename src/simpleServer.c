#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MYPORT 8622
#define RECVBUFFLEN 1024
int main(int argc, char ** argv) {
  int server_fd, client_fd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char heading[] = "This is server!";
  
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("0.0.0.0");
  server_address.sin_port = htons(MYPORT);
  server_len = sizeof(server_address);
  
  bind(server_fd, (struct sockaddr *) &server_address, server_len);
  listen(server_fd, 10);

  while(1) {
    char recv_buff[RECVBUFFLEN];
    memset(recv_buff, 0, RECVBUFFLEN);
    printf("server is waiting...\n");
    client_len = sizeof(client_address);
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
    read(client_fd, recv_buff, RECVBUFFLEN-1);
    write(client_fd, heading, sizeof(heading));
    printf("received from client : %s\n", recv_buff);
    close(client_fd);
  }

  close(server_fd);
  return 0;
}
