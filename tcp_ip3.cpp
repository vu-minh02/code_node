#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
void error (const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]){
if(argc<2){
    fprintf(stderr,"Port Nonot provided. Program terminated\n");
    exit(1);
}
    int sockfd, newsockfd, portno;//create socket file descriptor,port number
    int buffer1[10];//buffer store data
    int sum=0;//sum
    int n;
    struct sockaddr_in serv_addr,cli_addr;//address of server and client
    socklen_t clien;//length of client

    sockfd= socket(AF_INET,SOCK_STREAM,0);// IPv4, cach truyen du lieu, kh=ieu truyen tcp
    if(sockfd<0){
        error("Error opening Socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;//set giao thuc IPv4
    serv_addr.sin_port = htons(portno);//set port connect for server
    serv_addr.sin_addr.s_addr =  INADDR_ANY;//set addr ip for server
     
    if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
    error("Binding Failed");
     
listen(sockfd,5);
clien = sizeof(cli_addr);//length of cli_addr 
newsockfd = accept(sockfd,(struct  sockaddr *)&cli_addr, &clien);
if(newsockfd<0)
{
   error("Serve and client not accept");
}
while (1)
{
    bzero(buffer1,10);//delete buffer
    n=read(newsockfd,buffer1,10);
    if(n<0){
        error("Error on reading");
        }
         for(int i=0;i<10;i++){
            printf("so tu client: %d",buffer1[i]);
            sum+=buffer1[i];
        }
        printf("Client: %d\n",sum);
    bzero(buffer1,10);
    

    n=write(newsockfd,buffer1, 40);
    if(n<0){
        error("Error on writting");
    }
    
}
close(newsockfd);
close(sockfd);
return 0;

}
