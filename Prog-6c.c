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
void str_echo(int sockfd, struct sockaddr *cli_address, int clilen)
{
    int n;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    int addrlen;
    for (;;)
    {
        addrlen = clilen;
        n = recvfrom(sockfd, buffer, bufsize, 0, cli_address, &addrlen); //RECV BUFFER
        sendto(sockfd, buffer, n, 0, cli_address, addrlen);
    } //sendto
}
int main()
{
    int sockfd;
    struct sockaddr_in serv_address, cli_address;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) > 0) //sockfd
        printf("The socket was created\n");
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(16001);
    printf("The address before bind %s ...\n", inet_ntoa(serv_address.sin_addr));
    if (bind(sockfd, (struct sockaddr *)&serv_address, sizeof(serv_address)) == 0) //bind
        printf("Binding Socket\n");
    str_echo(sockfd, (struct sockaddr *)&cli_address, sizeof(cli_address));
    return 0;
}

//Client
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
void str_cli(FILE *fp, int sockfd, struct sockaddr *serv_address, int servlen)
{
    int bufsize = 1024, cont;
    char *buffer = malloc(bufsize);
    int addrlen = sizeof(struct sockaddr_in);
    while (fgets(buffer, bufsize, fp) != NULL)
    {
        sendto(sockfd, buffer, sizeof(buffer), 0, serv_address, servlen);
        if ((cont = recvfrom(sockfd, buffer, bufsize, 0, NULL, NULL) > 0))
        {
            fputs(buffer, stdout); // ECHO PRINTING..
        }
    }
    printf("\nEOF\n");
}
int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_address;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) > 0)
        printf("The Socket was created\n");
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(16001);
    inet_pton(AF_INET, argv[1], &serv_address.sin_addr);
    str_cli(stdin, sockfd, (struct sockaddr *)&serv_address, sizeof(serv_address));
    exit(0);
}
