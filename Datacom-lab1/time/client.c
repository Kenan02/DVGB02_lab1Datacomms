#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define MAXLENGHT 1024


int main(int argc, char *argv[])
{
    int sockfd, port, ip, serverlen, c; 
    struct sockaddr_in serveraddr; 
    uint32_t seconds;
    uint32_t oldtime = 2208988800;


    if(argc < 2){
        perror("Requires port number");
        exit(1); 
    }

    ip = atoi(argv[1]);
    port = atoi(argv[2]); 
     


    // skapar socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = INADDR_ANY; 
    serveraddr.sin_port = htons(port); 

    
    c = sendto(sockfd," ",0, 0, (const struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(c < 0){
        perror("Failed to send");
        exit(1); 
    }

         
    serverlen = sizeof(serveraddr); 
    c = recvfrom(sockfd, &seconds, sizeof(seconds),0, (struct sockaddr *) &serveraddr, (socklen_t *)&serverlen);
    if(c < 0){
        perror("Failed to recieve");
        exit(1); 
    }
    
    
    seconds = seconds - oldtime;
    time_t curr_time = seconds; 
    puts("");
    puts("Time from server");
    printf("%s \n", ctime(&curr_time));
    
    close(sockfd); 

    puts("");

   return 0; 
}
