//Server
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
#include<arpa/inet.h> 
int main(){ 
    int sd = socket(AF_INET , SOCK_STREAM , 0); 
    struct sockaddr_in serv = {0}; 
    char buff[100]; 
    serv.sin_family = AF_INET; 
    serv.sin_port = htons(15002); 
    serv.sin_addr.s_addr = INADDR_ANY; 
    bind(sd , (struct sockaddr *) &serv , sizeof(serv)); 
    listen(sd , 3); 
    int aid = accept(sd , NULL , NULL); 
     while(1)
    {
        int bytes = recv(aid , buff , sizeof(buff)-1 , 0);
        if(bytes <= 0)
            break;
        buff[bytes] = '\0';
        if(strncmp(buff , "end" , 3) == 0)
        {
            printf("Connection Closed\n");
            break;
        }
        printf("the command given is %s\n", buff);
        system(buff);
    }
    close(aid); 
    close(sd); 
    return 0; 
}

//Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
    int sd = socket(AF_INET , SOCK_STREAM , 0);
    struct sockaddr_in cli = {0};
    char buff[100];
    cli.sin_family = AF_INET;
    cli.sin_port = htons(15002);
    cli.sin_addr.s_addr = INADDR_ANY;
    connect(sd , (struct sockaddr *)&cli , sizeof(cli));
    while(1)
    {
        printf("enter your command: ");
        fgets(buff , sizeof(buff) , stdin);
        if(strncmp(buff , "end" , 3) == 0)
        {
            send(sd , buff , strlen(buff)+1 , 0);
            break;
        }
        send(sd , buff , strlen(buff)+1 , 0);
    }
    close(sd);
    return 0;
}
