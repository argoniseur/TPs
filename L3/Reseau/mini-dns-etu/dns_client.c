#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dns_packet_parsing.h"
#include "dns_server_rr_files.h"
#include "utils.h"


int main(int argc, char ** argv){
	
	if(argc != 4 && argc != 6){
		fprintf(stderr, "Usage: %s -s @IP_serveur_DNS [-p port] nom_de_domaine\n", argv[0]);
		exit(99);
	}
	
	
	
	
	
	char* message = malloc(4*sizeof(char));
	char* name = malloc(5*sizeof(char));
	name = "Bibi";
	message = "salut";
	int retour;
	retour = build_dns_request(message,name);
	
	print_dns_packet(message,retour);
	
	
	
	return 0;
}
