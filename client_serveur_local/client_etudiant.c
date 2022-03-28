#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>

#define HTTP_PORT   80
#define PORT_CUSTOM 50000

#define USED_PORT   PORT_CUSTOM


int main(int argc, char* argv[])
{
    int num_socket, num_connect, num_send, num_recv;
    struct sockaddr_in serveur;
    int port = USED_PORT;
    char IP[16] = "127.0.0.1"; 					// @ Ip du serveur

    char requette[] = "0";	// Requette
    //char requette[] = "GET / HTTP/1.1\r\nHost: 192.168.176.2\r\n\n";    // Requette HTTP
    char reponse[1000]; 						// Buffer pour la reception
         
    /******* Creation de la socket SOCK_STREAM : socket() ***************/
    num_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(num_socket < 0) {
        perror("Socket status : ");
    }

    /******* Connexion avec un serveur distant : connect() ***************/
    serveur.sin_family = AF_INET;
    serveur.sin_port = htons(port);
    serveur.sin_addr.s_addr = inet_addr(IP);

    num_connect = connect(num_socket, (struct sockaddr*) &serveur, sizeof(struct sockaddr));
    if(num_connect < 0) {
        perror("Connect status : ");
    }

    printf("\nReponses :\n");

    /*****************  Requette : send() ****************************/
    num_send = send(num_socket, requette, strlen(requette), 0);
    if(num_send < 0) {
        perror("Send status : ");
    }

    /*****************  Réponse : rcv () ****************************/
    num_recv = recv(num_socket, reponse, 1000, 0);
    if(num_recv < 0) {
        perror("Recv status : ");
    }
    printf("%s\n", reponse);


    /*****************  Fermeture socket : close() ******************/
    close(num_socket);
    printf("\nFin connexion\n");

    return 0;
}
