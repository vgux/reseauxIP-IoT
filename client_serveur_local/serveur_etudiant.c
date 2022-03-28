#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>

#define PORT_SERVEUR 		50000		// port d'écoute du serveur
#define IP_SERVEUR			"127.0.0.1"	//@IP serveur web

int main(int argc, char* argv[])
{
	int num_socket, num_bind, num_listen, num_accept;
	unsigned int size;
	struct sockaddr_in client;
	struct sockaddr_in serveur;
	char requette;
	char reponse0[]="Nous avons recu votre requete numero 0";
	char reponse1[]="Nous avons recu votre requete numero 1";
	char reponseDefaut[] = "Defaut";
	size=sizeof(struct sockaddr_in);

	/******* Creation de la socket SOCK_STREAM : socket() ***************/
	num_socket = socket(AF_INET, SOCK_STREAM, 0);
    perror("Socket status");

	/******* Association entre l'adresse IP et le port d'écoute : bind() ***/
	serveur.sin_family=AF_INET;
	serveur.sin_port=ntohs(PORT_SERVEUR);
	serveur.sin_addr.s_addr = inet_addr(IP_SERVEUR);

	num_bind = bind(num_socket, (struct sockaddr*) &serveur, sizeof(struct sockaddr_in));
	perror("Bind status");

	/******* Configuration des demandes de connexions : listen () ***/
	num_listen = listen(num_socket, 1);
	perror("Listen status");

	while(1){
		/******* Attente de nouvelle connexions : accept ()  **************/
		num_accept = accept(num_socket, NULL, NULL);
		perror("Accept status");

		/*****************  Réception de la requette : recv() **************/
		recv(num_accept, &requette, 1, 0);
		perror("Recv status");

		/*****************  Envoi de la réponse : send() *******************/
		switch(requette) {
			case '0' :
				send(num_accept, reponse0, strlen(reponse0)+1, 0);
				break;
			case '1' :
				send(num_accept, reponse1, strlen(reponse0)+1, 0);
				break;
			default :
				send(num_accept, reponseDefaut, strlen(reponse0)+1, 0);
		}

		/*********  Fermeture connexion avec le client : close() ***********/
		close(num_accept);
	}

	/*****************  Fermeture socket : close() ******************/
	close(num_socket);

	return 0;
}
