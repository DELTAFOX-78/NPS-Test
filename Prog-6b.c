//Server
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
void str_echo(int connfd)
{
    int n = 1;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    do
    {
        while ((n = recv(connfd, buffer, bufsize, 0)) > 0)
            send(connfd, buffer, n, 0);
    } while (n > 0);
}
int main()
{
    int cont, listenfd, connfd, addrlen;
    struct sockaddr_in address;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("The socket was created\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15001);
    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == 0)
        printf("Binding Socket\n");
    listen(listenfd, 3);
    printf("server is listening\n");
    for (;;)
    {
        addrlen = sizeof(struct sockaddr);
        connfd = accept(listenfd, (struct sockaddr *)&address, &addrlen);
        printf("The Client %s is Connected...on port%d\n",inet_ntoa(address.sin_addr),htons(address.sin_port));
        str_echo(connfd);
        close(listenfd);
    }
    return close(connfd);
}

//Client
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
void str_cli(FILE *fp, int sockfd)
{
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    while (fgets(buffer, bufsize, fp) != NULL)
    {
        send(sockfd, buffer, sizeof(buffer), 0);
        if (recv(sockfd, buffer, bufsize, 0) > 0)
            fputs(buffer, stdout);
    }
    printf("\nEOF\n");
    free(buffer);
}
int main(int argc, char *argv[])
{
    int create_socket;
    struct sockaddr_in address;
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("The socket was created\n");
    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    inet_pton(AF_INET, argv[1], &address.sin_addr);
    if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
        printf("The connection was accepted with the server %s...\n", argv[1]);
    str_cli(stdin, create_socket);
    return close(create_socket);
}
