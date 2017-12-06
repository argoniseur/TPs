#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr, htons
#include "dns_packet_parsing.h"
#include "dns_server_rr_files.h"

#define BUF_SIZE 1024

int main(int argc,char *argv[]){
    char* file_name;
    char rr_data[4];
    char dataTmp[4];
    unsigned char ipv4_addr[4];
    char domaine_name[100];
    int sock_id;
    struct sockaddr_in server_adr;
    struct sockaddr_in client_adr;
    socklen_t client_adr_len = sizeof(client_adr);
    char buffer[BUF_SIZE];
    int paquet_size;
    int portEcoute = atoi(argv[2]);
    char sub_domain[4];
    int server_type;
    char my_domain[4];
    /*Vérification de la cohérence des arguments*/
    if(argc != 3){
        fprintf(stderr, "Usage : ./%s ressourceRecords portUDP \n",argv[0] );
        exit(EXIT_FAILURE);
    }
    file_name = argv[1];
    /* Creation d'une socket en mode datagramme  */
    /*-------------------------------------------*/
    sock_id = socket(AF_INET, SOCK_DGRAM, 0);
    if ( sock_id < 0 ) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    /* Association adresse et port à la socket (bind)  */
    /*-------------------------------------------------*/

    /* Initialisation adresse locale du serveur  */
    memset(&server_adr, 0, sizeof(server_adr));
    server_adr.sin_family = AF_INET;
    server_adr.sin_port = htons(portEcoute); // htons: host to net byte order (short int)
    server_adr.sin_addr.s_addr = htonl(INADDR_ANY); // wildcard address

    if (bind(sock_id, (struct sockaddr *) &server_adr, sizeof(server_adr)) < 0) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }
    /* Réception des messages (attente active)  */
    /*------------------------------------------*/
    while (1) {
        memset(&rr_data,0,sizeof(rr_data));
        printf("\nServeur en attente...\n");
        client_adr_len = sizeof(client_adr);
        if (recvfrom(sock_id, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_adr, &client_adr_len) < 0) {
            perror("recvfrom error");
            exit(EXIT_FAILURE);
        }
        if((qname_from_question(buffer,sizeof(buffer),domaine_name))==-1){
            fprintf(stderr, "qname not ok");
        }
        server_type=read_server_type_from_conf(file_name,my_domain) ;
        /* Récupération du type de serveur*/
        /* En fonction du serveur on va au premier(TLD) ou au deuxieme(ROOT) point */
        int z=0;
        if(server_type == 1){
            for(int i=0;i<strlen(domaine_name);i++){
                if(domaine_name[i] == '.'){
                    z=i;
                }
            }
        }else{
            while(domaine_name[z] != '.'){
                z++;
            }
        }
        char tmp1[4];
        char tmpX[4];
        domaine_name[z] = ' ';
        sscanf(domaine_name,"%s %s",tmp1,sub_domain);
        /* Ecriture du préfixe */
        /* -------------------- */
        if(server_type == 3){
            if((strcmp(sub_domain,my_domain) != 0) || (get_rr_data_from_name(file_name,tmp1,rr_data)==0)){
                build_dns_reply_name_error(buffer);
            }else{
                for(int i=0;i<strlen(rr_data);i++){
                    if(rr_data[i] == '.'){
                        rr_data[i] = ' ';
                    }
                }
                char test1[2];
                char test2[2];
                char test3[2];
                char test4[2];
                sscanf(rr_data,"%s %s %s %s",test1,test2,test3,test4);
                ipv4_addr[0]=atoi(test1);
                ipv4_addr[1]=atoi(test2);
                ipv4_addr[2]=atoi(test3);
                ipv4_addr[3]=atoi(test4);
                paquet_size=build_dns_answer(buffer,ipv4_addr);
            }
        }else{
            if(get_rr_data_from_name(file_name,sub_domain,rr_data)==0){
                build_dns_reply_name_error(buffer);
            }
            memcpy(tmpX,rr_data,strlen(rr_data)*4);
            if(get_rr_data_from_name(file_name,rr_data,dataTmp)==0){
                build_dns_reply_name_error(buffer);
                ipv4_addr[0]=0;
                ipv4_addr[1]=0;
                ipv4_addr[2]=0;
                ipv4_addr[3]=0;
            }else{
                for(int i=0;i<strlen(dataTmp);i++){
                    if(dataTmp[i] == '.'){
                        dataTmp[i] = ' ';
                    }
                }
                char test1[2];
                char test2[2];
                char test3[2];
                char test4[2];
                sscanf(dataTmp,"%s %s %s %s",test1,test2,test3,test4);
                ipv4_addr[0]=atoi(test1);
                ipv4_addr[1]=atoi(test2);
                ipv4_addr[2]=atoi(test3);
                ipv4_addr[3]=atoi(test4);
            }
            paquet_size=build_dns_additional(buffer,sub_domain,tmpX,ipv4_addr);
        }
        
        print_dns_packet(buffer,paquet_size);
        /* Envoi de la réponse  */
        if ( (sendto(sock_id, buffer, paquet_size, 0, (struct sockaddr*) &client_adr, sizeof(client_adr))) < 0) {
            perror("sendto error");
            exit(EXIT_FAILURE);
        }
        printf("--> Message envoyé au client.\n");
    } /* while */
}

