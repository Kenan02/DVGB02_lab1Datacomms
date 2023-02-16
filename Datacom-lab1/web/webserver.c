//Gjort av Oliver Raner och Kenan Sahinovic
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

#define SERVER_PORT 8080 // server portnummer

void client_send(int client_socket, char *request_t);

int main(int argc, char *argv[])
{
    char header[1024];
    char client_r[1024];
    long fsize;

    // server socket
    int server_s;
    server_s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_a;
    server_a.sin_family = AF_INET;
    server_a.sin_port = htons(SERVER_PORT);
    server_a.sin_addr.s_addr = INADDR_ANY;

    bind(server_s, (struct sockaddr *)&server_a, sizeof(server_a));

    listen(server_s, 5);

    int client_s;

    while (1)
    {

        client_s = accept(server_s, 0, 0);
        read(client_s, client_r, sizeof(client_r));

        printf("\n%s\n", client_r);

        char *request_t = strtok(client_r, " \n\r");
        char *file_t = strtok(NULL, " \n\r");
        char *HTTP = strtok(NULL, " \n\r");
        file_t += 1; // för att ta bort "/"
        FILE *f;

        if (strcmp(request_t, "kan ej kommentera ut") == 0)
        {
            puts(request_t);
        }
        if (strcmp(file_t, "") == 0)
        {
            sprintf(header, "%s 200 OK\r\n\r\n", HTTP);
            write(client_s, header, strlen(header));
        }
        else if (strcmp(file_t, "favicon.ico") == 0)
        {
            sprintf(header, "%s 400 NOT OK\r\n\r\n", HTTP);
            write(client_s, header, strlen(header));
        }
        else
        {
            f = fopen(file_t, "r");
            fseek(f, 0, SEEK_END);
            fsize = ftell(f);
            fseek(f, 0, SEEK_SET);

            char *buffer = malloc(fsize + 1);
            fread(buffer, 1, fsize, f);

            if (strcmp(file_t, "index.html") == 0)
            {
                sprintf(header, "%s 200 OK\r\nContent-Type: text/html\r\n\r\n", HTTP);
            }
            else if (strcmp(file_t, "img/quokka.jpg") == 0)
            {
                sprintf(header, "%s 200 OK\r\nContent-Type: image/jpg\r\n\r\n", HTTP);
            }

            write(client_s, header, strlen(header));
            write(client_s, buffer, fsize);
            fclose(f);
            free(buffer);
        }

        close(client_s);
        fflush(stdout);
    }

    return 0;
}
