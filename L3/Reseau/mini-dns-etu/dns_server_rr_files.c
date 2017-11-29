/* v07/16, v10/17 E. Lavinal (Univ. of Toulouse) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dns_server_rr_files.h" // Constants: ROOT, TLD,...

#define MAX_LINE 100
#define SERVER_TYPE "SERVER_TYPE"

/*
 * Read server type from config file
 *
 * Parameters:
 *   file_name -- the config file name
 *   my_domain -- the size of packet (input != output)
 *
 * Return value: server type (ROOT, TLD or AUTHORITATIVE)
 */
int read_server_type_from_conf(const char * file_name, char * my_domain) {

    FILE *file = NULL;
    char line[MAX_LINE];
    char server_type_name[32], server_type_value[32];
    int found = 0;

    file = fopen(file_name, "r");
    if (file == NULL) {
        perror("[RR files] Problem opening file.\n");
        exit(EXIT_FAILURE);
    }

    // fgets(char[] dest, int size, FILE* stream);
    while ( !found && fgets(line, sizeof(line), file) ) {

        if (line[0] != '#') {

            if ( strncmp(line, SERVER_TYPE, strlen(SERVER_TYPE)) == 0 ) {

                sscanf(line, "%s %s %s", server_type_name, server_type_value, my_domain);

                if (strncmp(server_type_value, "ROOT", strlen("ROOT"))==0)
                    found = ROOT;
                if (strncmp(server_type_value, "TLD", strlen("TLD"))==0)
                    found = TLD;
                if (strncmp(server_type_value, "AUTHORITATIVE", strlen("AUTHORITATIVE"))==0)
                    found = AUTHORITATIVE;
            }
        }
    }
    fclose(file);
    return found;
}


/*
 * Read Resource Record Data from config file
 *
 * Parameters:
 *   file_name -- the config file name
 *   domain_name -- the domain we are looking for
 *   rr_data -- the resource associated to that domain (A or NS type)
 *
 * Return value: 1 if domain name found, else 0
 */
int get_rr_data_from_name(const char * file_name, const char * domain_name, char * rr_data) {

    FILE *file = NULL;
    char line[MAX_LINE];
    char name[32], class[8], type[8];
    int found = 0;

    file = fopen(file_name, "r");
    if (file == NULL) {
        perror("[RR files] Problem opening file.\n");
        exit(EXIT_FAILURE);
    }
    printf(">>> %s %s \n", file_name, domain_name);
    // fgets(char[] dest, int size, FILE* stream);
    while ( !found && fgets(line, sizeof(line), file) ) {

        if (line[0] != '#') {
            // printf("[DEBUG] line : %s", line);
            sscanf(line, "%s", name);
            if ( strcmp(name, domain_name) == 0 ) {

                sscanf(line, "%s %s %s %s", name, class, type, rr_data);
                printf("name %s class %s type %s addr %s \n", name, class, type, rr_data);
                found = 1;
            }
        }
    }
    fclose(file);

    return found;
}
