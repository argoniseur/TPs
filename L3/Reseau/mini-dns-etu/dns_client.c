/********************************
**      TP SOCKETS TCP/IP      **
**  Hello World UDP (client)   **
********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr, htons
#include "dns_packet_parsing.h"
#include "utils.h"

#define MSG_MAX_SIZE 1024
//#define MSG "Hello World!"

/*=====================
= Programme principal =
======================*/
int main(int argc, char * argv[]) {

    int sock_id, server_port;
    char server_ip[16]; // address as a string
    char domaine_name[100];
    char message[MSG_MAX_SIZE];
    struct sockaddr_in server_adr;
    socklen_t size_server;
    int size;
    int rcode;
    unsigned char ip_addr_domaine[4];

    

    if (argc != 4 && argc != 6) {
        printf("Usage: %s -s @IP_serveur_DNS [-p port] nom_de_domaine\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /*Initialisation*/
    strcpy(server_ip, argv[2]);
    if(argc == 6){
        server_port = atoi(argv[4]);
        strcpy(domaine_name,argv[5]);
    }
    else{
        server_port = 53;
        strcpy(domaine_name,argv[3]);
    }
    
    

    /* Creation d'une socket en mode datagramme  */
    /*-------------------------------------------*/
    if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    /* Initiatlisation de l'adresse du serveur */
    /*-----------------------------------------*/
    memset(&server_adr, 0, sizeof(server_adr));
    server_adr.sin_family = AF_INET;
    server_adr.sin_port = htons(server_port);
    server_adr.sin_addr.s_addr = inet_addr(server_ip);
     
    /*Construction de la requète dns*/
    size_server = sizeof(server_adr);
    size = build_dns_request(message,domaine_name);

    /* Envoi du message au serveur */
    /*-----------------------------*/
    if((sendto(sock_id, message, size, 0, (struct sockaddr*) &server_adr, sizeof(server_adr))) < 0){
        perror("sendto error");
        exit(EXIT_FAILURE);
    }

    /* Réception de la réponse */
    /*-------------------------*/
    if((recvfrom(sock_id,message, MSG_MAX_SIZE, 0, (struct sockaddr*) &server_adr, &size_server)) < 0){
        perror("recvfrom()");
        exit(EXIT_FAILURE);
    }
    

    rcode = no_such_name(message);
    if(rcode == 0){
        ip_from_answer(message,ip_addr_domaine);
        print_ip_v4(ip_addr_domaine);
    }
    else{
        printf("No such name\n");
    }

    /* Fermeture de la socket */
    /*------------------------*/
    close(sock_id);

    return 0;
}

