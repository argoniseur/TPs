#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "utils.h"
#include "dns_server_rr_files.h"
#include "dns_packet_parsing.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Usage: %s fichier_ressource port_UDP\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int sock_id,server_port;
    struct sockaddr_in server_adr;
    struct sockaddr_in client_adr;
    socklen_t client_adr_len = sizeof(client_adr);
    char *file_name;
    char buffer[BUF_SIZE];
    FILE *fich = NULL;
    char domain_name[100];
    char prefix_domain_name[100];
    char rr_data[4];
    unsigned char ipv4_adress[4];
    int packet_size;
        
    
    
    if((fich = fopen(argv[1],"r")) == NULL){
        perror("Erreur fichier");
        exit(EXIT_FAILURE);
    }
    
    file_name = argv[1];

    /* Creation d'une socket en mode datagramme  */
    if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    /* Initialisation adresse locale du serveur  */
    server_port = atoi(argv[2]);
    memset(&server_adr, 0, sizeof(server_adr));
    server_adr.sin_family = AF_INET;
    server_adr.sin_port = htons(server_port);
    server_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    

    if(bind(sock_id, (struct sockaddr *) &server_adr, sizeof(server_adr)) < 0){
        perror("Erreur bind");
        exit(EXIT_FAILURE);
    }

    /* Réception des messages */
    while(1){

        printf("\nServeur en attente...\n");
        client_adr_len = sizeof(client_adr);
        if(recvfrom(sock_id, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_adr, &client_adr_len) < 0){
            perror("Erreur recvfrom");
            exit(EXIT_FAILURE);
        }
        //Verification de la validité du nom de domaine
        if((qname_from_question(buffer, sizeof(buffer), domain_name)) == -1){
            fprintf(stderr,"Qname invalide");
        }
        
        /*Recupération du préfixe*/
        int i = 0;
        int fin = 0;
        while(i < strlen(domain_name) && !fin){
            if(domain_name[i] == '.'){
                domain_name[i] = ' ';
                fin = 1;
            }
            i++;
        }
        sscanf(domain_name, "%s %s", prefix_domain_name,domain_name);
        
        //Construction de l'adresse ipv4 lié au nom de domaine
        char domain[2];
        read_server_type_from_conf(file_name, domain);
        if(get_rr_data_from_name(file_name, prefix_domain_name, rr_data) == 0 || strcmp(domain_name, domain) != 0){
            build_dns_reply_name_error(buffer);
            for(i = 0; i<4; i++)
                ipv4_adress[i] = 0;
        }
        else{
            for(int i = 0; i<strlen(rr_data); i++){
                if(rr_data[i] == '.'){
                    rr_data[i] = ' ';
                }
            }
            char test1[2], test2[2], test3[2], test4[2];
            sscanf(rr_data, "%s %s %s %s", test1, test2, test3, test4);
            ipv4_adress[0] = atoi(test1);
            ipv4_adress[1] = atoi(test2);
            ipv4_adress[2] = atoi(test3);
            ipv4_adress[3] = atoi(test4);
            packet_size = build_dns_answer(buffer, ipv4_adress);         
        }
            
        /* Envoi de la réponse  */
        if((sendto(sock_id, buffer, packet_size, 0, (struct sockaddr *)&client_adr, sizeof(client_adr))) < 0){
            perror("sendto()");
            exit(EXIT_FAILURE);
        }
        
        printf("--> Message envoyé au cient.\n");
    }

    close(sock_id);
    return 0;
}

