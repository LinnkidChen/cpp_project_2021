#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define WAIT_USEC 5
#define WAIT_SEC 0
#define BUFFER_SIZE 10000
int main() {
  int sock = 0, valread, retval;
  struct sockaddr_in serv_addr;

  char buffer[BUFFER_SIZE] = {0};
  std::string temp_str;
  fd_set rfds;
  struct timeval tv;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("connect");
    return -1;
  }
  int status = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);

  if (status == -1) {
    perror("calling fcntl");
  }
  int opt = 65535;
  if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  opt = 65535;
  if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  for (;;) {

    tv.tv_usec = WAIT_USEC;
    tv.tv_sec = WAIT_SEC;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(sock, &rfds);

    retval = select(sock + 1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
      perror("retval");
    } else if (retval) {

      if (FD_ISSET(sock, &rfds)) { // recv is ready
        memset(buffer, 0, BUFFER_SIZE);
        retval = read(sock, buffer, BUFFER_SIZE);
        while (retval != -1) {
          puts(buffer);
          memset(buffer, 0, BUFFER_SIZE);
          retval = recv(sock, buffer, BUFFER_SIZE, 0);
        }
        std::puts(buffer);
        continue;
        // std::cout << buffer;
      }
      if (FD_ISSET(0, &rfds)) { // cin is ready
        std::cin >> temp_str;
        send(sock, temp_str.c_str(), temp_str.size() + 1, 0);
        temp_str.clear();
        continue;
      }
    } else {
      // std::cout << "No data in 5 secs" << std::endl;
    }
  }

  return 0;
}