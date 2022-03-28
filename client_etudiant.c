#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>

#define HTTP_PORT   80

int main(int argc, char* argv[])
{
    int num_socket, num_connect, num_send, num_recv;
    struct sockaddr_in serveur;
    int port = HTTP_PORT;
    char IP[16] = "192.168.176.2"; 					// @ Ip du serveur

    //char requette[] = "GET / HTTP/1.0 \n\n";	// Requette HTTP
    char requette[] = "GET / HTTP/1.0\r\nHost: 192.168.176.2\r\n\n";    // Requette HTTP
    char reponse[1000]; 						// Buffer pour la reception
         
    /******* Creation de la socket SOCK_STREAM : socket() ***************/
    num_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(num_socket != 0) {
        perror("Error Socket : ");
    }

    /******* Connexion avec un serveur distant : connect() ***************/
    serveur.sin_family = AF_INET;
    serveur.sin_port = htons(port);
    serveur.sin_addr.s_addr = inet_addr(IP);

    num_connect = connect(num_socket, (struct sockaddr*) &serveur, sizeof(struct sockaddr));
    if(num_connect != 0) {
        perror("Error connect : ");
    }


    /*****************  Requette : send() ****************************/
    num_send = send(num_socket, requette, strlen(requette)+1, 0);
    if(num_send != 0) {
        perror("Error send : ");
    }

    /*****************  Réponse : rcv () ****************************/
    num_recv = recv(num_socket, reponse, 1000, 0);
    if(num_recv != 0) {
        perror("Error recv : ");
    }
    /*****************  Fermeture socket : close() ******************/
    close(num_socket);

    return 0;
}
