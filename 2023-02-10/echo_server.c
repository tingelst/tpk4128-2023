#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h>    // memset
#include <stdbool.h>   // true, false

int main(int argc, char const *argv[])
{

  int server_file_descriptor;
  int client_file_descriptor;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int len;
  int port = 65432;
  char buffer[1024];

  server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (server_file_descriptor < 0)
  {
    perror("Cannot create socket");
    exit(1);
  }
  server.sin_family = AF_INET;
  // server.sin_addr.s_addr = INADDR_ANY;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(port);
  len = sizeof(server);
  if (bind(server_file_descriptor, (struct sockaddr *)&server, len) < 0)
  {
    perror("Cannot bind sokcet");
    exit(2);
  }
  if (listen(server_file_descriptor, 10) < 0)
  {
    perror("Listen error");
    exit(3);
  }
  while (true)
  {
    len = sizeof(client);
    printf("Waiting for clients\n");
    if ((client_file_descriptor = accept(server_file_descriptor, (struct sockaddr *)&client, &len)) < 0)
    {
      perror("accept error");
      exit(4);
    }
    char *client_ip = inet_ntoa(client.sin_addr);
    printf("Accepted new connection from a client %s:%d\n", client_ip, ntohs(client.sin_port));
    memset(buffer, 0, sizeof(buffer));
    int size = read(client_file_descriptor, buffer, sizeof(buffer));
    if (size < 0)
    {
      perror("read error");
      exit(5);
    }
    printf("Received %s from client\n", buffer);
    if (write(client_file_descriptor, buffer, size) < 0)
    {
      perror("write error");
      exit(6);
    }
    close(client_file_descriptor);
  }
  close(server_file_descriptor);
  return 0;
}
