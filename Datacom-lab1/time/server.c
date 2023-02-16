// Server side implementation of UDP client-server model
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

void server_print(char text[])
{
    printf("Timeserver: %s\n", text);
}

int main(int argc, char *argv[])
{
    int sockfd, portnum, clientlen;
    char buffer[MAXLENGHT];
    // char response[MAXLENGHT];
   

    int c; // check variable for recvfrom

    struct sockaddr_in serveraddr, clientaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR creating socket");
    }
    server_print("Socket Created");

    portnum = atoi(argv[1]);

    serveraddr.sin_family = AF_INET;         // IPv4 så typ tillhörighet
    serveraddr.sin_addr.s_addr = INADDR_ANY; // vad den kan binda till i detta fall 'any'
    serveraddr.sin_port = htons(portnum);

    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Error binding");
        exit(1);
    }

    clientlen = sizeof(clientaddr);
    c = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&clientlen);
    if (c < 0)
    {
        perror("Error recieving");
        exit(1);
    }
    uint32_t rfc_time = 2208988800;
    uint32_t seconds;
    seconds = time(NULL) + rfc_time;

    time_t curr_time = seconds; 
    puts("");
    puts("Time in server");
    printf("%s \n", ctime(&curr_time));      


    c = sendto(sockfd, &seconds, sizeof(seconds), 0, (const struct sockaddr *)&clientaddr, sizeof(clientaddr));
    if (c < 0)
    {
        perror("Failed to send");
        exit(1);
    }

    close(sockfd);

    server_print("Socket closed");

    return 0;
}
