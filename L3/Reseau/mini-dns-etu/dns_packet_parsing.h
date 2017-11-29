/* v09/16, E. Lavinal (Univ. of Toulouse) */

#ifndef __DNS_PP_H__
#define __DNS_PP_H__

// ============================================================
//         PRINT FUNCTION
// ============================================================

/*
 * Debug function. Print DNS packet.
 */
void print_dns_packet(char * packet, int size);

/*
 * Debug function. Print packet in hex.
 */
void dump_hex(char * packet, int size);


// ============================================================
//         EXTRACT DATA FROM DNS MESSAGE
// ============================================================

/*
 * Return the number of answers in DNS packet
 */
int count_answer(char * packet);

/*
 * Return packet's RCODE (0 no error, 3 name error)
 */
int no_such_name(char * packet);


/*
 * Get QNAME from DNS request (question section)
 * Parameters:
 *   packet -- the DNS request
 *   size -- the packet's size
 *   name -- the resulting question name as a string
 * Returns:
 *     1 if qname ok
 *    -1 otherwise
 */
int qname_from_question(char * packet, int size, char * name);

/*
 * Extract IP address (4 bytes array) from DNS answer section
 * (we suppose here only one answer)
 */
void ip_from_answer(char * packet, unsigned char ipv4_addr[4]) ;

/*
 * Extract IP address (4 bytes array) from DNS additionnal section
 * (we suppose here only one additionnal section)
 */
void ns_ip_from_add_section(char * packet, unsigned char ipv4_addr[4]) ;


// ============================================================
//             BUILDING DNS REQUEST
// ============================================================

/*
 * Build DNS request from domain name
 * (Header + Question sections)
 *
 * Parameters:
 *   message -- the buffer to build the request
 *   name --  the domain name for the question
 * Returns:
 *   the packet's size
 */
int build_dns_request(char * message, char * name);


// ============================================================
//             BUILDING DNS RESPONSES
// ============================================================

/*
 * Build a DNS response with one answer (type 'A')
 *
 * NOTE: We are REMOVING AUTHORITATIVE and ADDITIONAL sections if any...
 *
 * Parameters:
 *   packet -- the packet containing the query and to which an answer
 *             section will be added
 *   ipv4_addr --  the IP addr to put in the record data
 * Returns:
 *   packet's size
 */
int build_dns_answer(char * packet, unsigned char ip_addr[4]);

/*
 * Build a DNS response with 1 RR in Authority section and 1 RR in Additional section
 * NOTE: if fields in the authority or additional sections are present
 *       in the query, they are OVERWRITTEN !
 *
 * Parameters:
 *   packet -- the packet containing the query and to which authority and additional
 *             sections will be addded
 *   sub_domain --  the sub domain string
 *   ns -- the name server (string) of that domain
 *   ns_ip_addr -- the ip address (4 bytes array) of the name server (NS)
 * Returns:
 *   packet's size
 */
int build_dns_additional(char * packet, char * sub_domain, char * ns, unsigned char ipv4_addr[4]);

/*
 * Create a DNS reply name error packet
 *
 * Parameters:
 *   packet -- the packet used to build the reply
 */
void build_dns_reply_name_error(char * packet);


#endif
