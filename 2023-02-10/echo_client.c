#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // write, read, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h>    // strlen, memset

int main(int argc, char const *argv[])
{

  int socket_file_descriptor;
  struct sockaddr_in server_address;
  int len;
  int port = 65432;
  char *server_ip = "127.0.0.1";

  char *buffer = "hello server";

  socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_file_descriptor < 0)
  {
    perror("Cannot create socket");
    exit(1);
  }
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(server_ip);
  server_address.sin_port = htons(port);
  len = sizeof(server_address);
  if (connect(socket_file_descriptor, (struct sockaddr *)&server_address, len) < 0)
  {
    perror("Cannot connect to server");
    exit(2);
  }

  if (write(socket_file_descriptor, buffer, strlen(buffer)) < 0)
  {
    perror("Cannot write");
    exit(3);
  }
  char recv[1024];
  memset(recv, 0, sizeof(recv));
  if (read(socket_file_descriptor, recv, sizeof(recv)) < 0)
  {
    perror("cannot read");
    exit(4);
  }
  printf("Received %s from server\n", recv);
  close(socket_file_descriptor);
  return 0;
}
