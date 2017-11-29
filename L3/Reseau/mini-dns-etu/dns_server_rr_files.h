/* v07/16, v10/17 E. Lavinal (Univ. of Toulouse) */

#ifndef __RR_FILES_H__
#define __RR_FILES_H__

#define ROOT 1
#define TLD 2
#define AUTHORITATIVE 3

/*
 * Read server type from config file
 *
 * Parameters:
 *   file_name -- the config file name
 *   my_domain -- the domain managed by the server (from the config file)
 *
 * Return value: server type (ROOT, TLD or AUTHORITATIVE)
 */
int read_server_type_from_conf(const char * file_name, char * my_domain) ;

/*
 * Read Resource Record Data from config file
 *
 * Parameters:
 *   file_name -- the config file name
 *   domain_name -- the domain we are looking for
 *   rr_data -- the resource associated to that domain (A or NS type)
 *
 * TODO. include TTL in file?
 *
 * Return value: 1 if domain name found, else 0
 */
int get_rr_data_from_name(const char * file_name, const char * domain_name, char * rr_data) ;

#endif
