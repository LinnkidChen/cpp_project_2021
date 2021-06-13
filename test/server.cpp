#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

using std::string;
int main(int argc, char const *argv[]) {
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  string hello = "Hello from server";

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  std::ifstream fin;
  std::ofstream fout;

  int fin_fd;
  fin_fd = open("snd_buf.txt", O_RDONLY);
  std::cout << fin_fd << std::endl;
  fout.open("rcv_buf.txt");
  fd_set rfds;
  struct timeval tv;
  int retval;

  for (;;) {
    FD_ZERO(&rfds);
    FD_SET(fin_fd, &rfds);

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    retval = select(fin_fd + 1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
      perror("select()");
    else if (retval)
      printf("Data is available now.\n");
    /* FD_ISSET(0, &rfds) will be true. */
    else
      printf("No data within five seconds.\n");
  }
  return 0;
}