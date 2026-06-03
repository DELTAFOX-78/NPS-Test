//Server
#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<arpa/inet.h> 
int main(){ 
    int sd = socket(AF_INET , SOCK_STREAM , 0); 
    struct sockaddr_in serv = {0}; 
    char fname[50]; 
    char buff[200]; 
    serv.sin_family = AF_INET; 
    serv.sin_port = htons(15002); 
    serv.sin_addr.s_addr = INADDR_ANY; 
    bind(sd , (struct sockaddr *)&serv,sizeof(serv)); 
    listen(sd,3); 
    int aid = accept(sd , NULL , NULL); 
    int bytes = recv(aid , fname , 50 , 0); 
    fname[bytes] = '\0'; 
    printf(" the file name requested %s\n",fname); 
    int fd = open(fname , O_RDONLY); 
    if(fd < 0){ 
        printf("File not found\n"); 
    }else{ 
        int cnt; 
        while((cnt = read(fd , buff , sizeof(buff))) > 0){ 
            send(aid , buff  , cnt ,0); 
        } 
        close(fd); 
    } 
    printf("Request completed \n"); 
    close(aid); 
    close(sd); 
    return 0; 
}

//Client
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <arpa/inet.h>
 
int main(){ 
    int sd = socket(AF_INET , SOCK_STREAM , 0); 
    struct sockaddr_in serv = {0}; 
    char fname[50]; char buff[200]; 
    serv.sin_family = AF_INET; 
    serv.sin_port = htons(15002); 
    serv.sin_addr.s_addr = INADDR_ANY; 
     
    connect(sd , (struct sockaddr*) &serv , sizeof(serv)); 
    printf("enter the file name\n"); 
    scanf("%s",fname); 
    send(sd,fname , sizeof(fname) , 0); 
    int cnt = 0; 
    while((cnt = recv(sd , buff , sizeof(buff) , 0)) > 0){ 
        write(1 , buff , cnt); 
    } 
    printf("ended"); 
    close(sd); 
    return 0; 
} 
