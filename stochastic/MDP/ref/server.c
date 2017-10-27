//  Server side C / C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#define PORT 3000
int main(int argc,  char const *argv[])
{
    int server_fd,  new_socket,  valread;
    struct sockaddr_in address;
    int opt =  1;
    int addrlen =  sizeof(address);
    char buffer[1024] =  {0};
    char *hello =  "6 6 2 2 2 2 0 1 3 3 4 3 0 0 5 5";

    //  Creating socket file descriptor
    if ((server_fd =  socket(AF_INET,  SOCK_STREAM,  0)) ==  0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //  Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd,  SOL_SOCKET,  SO_REUSEADDR |  SO_REUSEPORT,
                   & opt,  sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family =  AF_INET;
    address.sin_addr.s_addr =  INADDR_ANY;
    address.sin_port =  htons( PORT );

    //  Forcefully attaching socket to the port 8080
    if (bind(server_fd,  (struct sockaddr *) & address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,  3) <  0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket =  accept(server_fd,  (struct sockaddr *) & address,
                              (socklen_t *) & addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread =  read( new_socket,  buffer,  1024);
    printf("%s\n", buffer );
    send(new_socket,  hello,  strlen(hello),  0 );
    int e = 15;
    while(e > 0){
        e--;
        int a = 0;
        char *msg = "0 1 2 2 3 3";
        while(a < 15){
            valread =  read( new_socket,  buffer,  1024);
            printf("%s\n", buffer );
            send(new_socket,  msg, strlen(msg),  0 );
            printf("Hello message sent\n");
            a++;
        }
        if(e % 4 == 0) msg = "win";
        else msg = "lose";
        valread =  read( new_socket,  buffer,  1024);
        printf("%s\n", buffer );
        send(new_socket,  msg, strlen(msg),  0 );
    }
    return 0;
}
