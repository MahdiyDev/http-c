#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEADER_LEN 88

void send_json(int fd, char *buf, size_t len) {
  int header_size = HEADER_LEN + len;

  char *header_buf;

  char header[HEADER_LEN] = "HTTP/1.1 200 OK\r\n"
                            "Content-type: application/json; charset=utf-8\r\n"
                            "Content-length: %u\r\n"
                            "\r\n"
                            "%s";

  header_buf = malloc(header_size);

  sprintf(header_buf, header, len, buf);

  printf("%s\n", header_buf);

  write(fd, header_buf, header_size);

  free(header_buf);

  close(fd);
}

int main(void) {
  int listenfd, connfd;

  struct sockaddr_in serveradrr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&serveradrr, 0, sizeof(serveradrr));

  serveradrr.sin_family = AF_INET;
  serveradrr.sin_port = htons(9999);
  serveradrr.sin_addr.s_addr = INADDR_ANY;

  if (bind(listenfd, (struct sockaddr *)&serveradrr, sizeof(serveradrr)) < 0) {
    printf("bind error!\n");
    exit(1);
  }

  listen(listenfd, 10);

  char *buf = "{\"message\":\"Not authorization\"}";

  for (;;) {
    connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

    send_json(connfd, buf, strlen(buf));
  }

  return 0;
}
