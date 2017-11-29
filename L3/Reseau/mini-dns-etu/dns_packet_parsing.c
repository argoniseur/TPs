/* v09/16, E. Lavinal (Univ. of Toulouse) */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  // uint16_t...
#include <string.h>  // strings, memcpy...
#include <time.h>      // rand()

/*  extract from [RFC 1035]

All communications inside of the domain protocol are carried in a single
format called a message.  The top level format of message is divided
into 5 sections (some of which are empty in certain cases) shown below:

    +---------------------+
    |        Header       |
    +---------------------+
    |       Question      | the question for the name server
    +---------------------+
    |        Answer       | RRs answering the question
    +---------------------+
    |      Authority      | RRs pointing toward an authority
    +---------------------+
    |      Additional     | RRs holding additional information
    +---------------------+

==> The header:

                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+



==> The question:

                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                     QNAME                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QTYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QCLASS                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

==> The answer, authority, and additional sections
    all share the same format (a variable number of
    resource records):

                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                                               /
    /                      NAME                     /
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     CLASS                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TTL                      |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                   RDLENGTH                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
    /                     RDATA                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/


#define QDCOUNT 5
#define ANCOUNT 7
#define NSCOUNT 9
#define ARCOUNT 11
#define QUESTION_INDEX 12


// ============================================================
//         PRINT FUNCTIONS
// ============================================================

/*
 * Print Resource Record (in answer, authority, or additional section).
 *
 * Note. We don't support NAMES with pointers (cf message compression).
 *       Only Name format with a sequence of labels ending with a zero octet.
 */
void print_rr(char * packet, int * index) {

    int i = *index;
    int type;

    printf("--> RR \n");

    // Name
    printf("  NAME: ");
    if (packet[i]==(char) 192) { // 1100 0000 (pointer code)
        printf("Name is a pointer...\n");
        i=i+1+2; // pointer=2B, TYPE=2B
    } else {
        while (packet[i]!=0) {
            printf("%c", packet[i++]);
        }
        printf("\n");
        i=i+2; // TYPE=2B
    }

    // Type
    printf("  TYPE : %d\n", packet[i]);
    type=packet[i];
    i=i+2;

    // Class
    printf("  CLASS : %d\n", packet[i]);
    i=i+4;

    // TTL
    printf("  TTL : %d\n", packet[i]);
    i=i+2;

    // RDLENGTH
    int rd_length = packet[i];
    printf("  RDLENGTH : %d\n", rd_length);

    // RDATA
    i++;
    printf("  RDATA: ");
    for (int j=0; j<rd_length; j++) {
        if (type==1) // A --> IPv4 addr
            printf("%d", (unsigned char) packet[i++]);
        else // NS
            printf("%c", packet[i++]);
    }
    printf("\n");

    *index = i;
}

/*
 * Debug function. Print DNS packet.
 * If the underlying transport is TCP then the offset should be 2
 * (rfc7766 --> TCP Message Length Field of 2 bytes before DNS message)
 */
void print_dns_packet(char * packet, int size) {

    uint16_t id, qdcount, ancount, nscount, arcount;
    uint16_t qtype, qclass;

    printf("===== DNS packet =====\n");

    printf("dns packet size: %d \n", size);

    /* ID */
    id = packet[1] + (packet[0]*256);
    printf("packet id 0x%x \n", id);

    /* QR code == 0 --> query, == 1 --> response */
    /* Bitwise AND */
    if ( (packet[2] & 128) == 128 ) {
        printf("this message is a response\n");
    }
    else {
        printf("this message is a query\n");
    }

    /* QDCOUNT  an unsigned 16 bit integer specifying the number of
               entries in the question section. */
    qdcount = packet[QDCOUNT] + (packet[QDCOUNT-1]*256);

    /* ANCOUNT  an unsigned 16 bit integer specifying the number of
                resource records in the answer section. */
    ancount = packet[ANCOUNT] + (packet[ANCOUNT-1]*256);

    /* NSCOUNT  an unsigned 16 bit integer specifying the number of name
                server resource records in the authority records section. */
    nscount = packet[NSCOUNT] + (packet[NSCOUNT-1]*256);

    /* ARCOUNT  an unsigned 16 bit integer specifying the number of
                resource records in the additional records section. */
    arcount = packet[ARCOUNT] + (packet[ARCOUNT-1]*256);

    printf("qdcount: %d ancount: %d nscount: %d arcount: %d\n", qdcount, ancount, nscount, arcount);

    /* starting from octet 12 is the question section */

    int index=QUESTION_INDEX, j=0, i=0, label_len;
    char qname[255];

    /* Print question section */
    /* ---------------------- */
    printf("*** Question section:\n");
    while (qdcount>0) {

        while ( packet[index]!=0 && (index < size) ) {

            label_len = packet[index++];
            for (j=0; j<label_len; j++) {
                qname[i++] = packet[index++];
            }
            qname[i++] = '.';
        }

        /* make qname a string */
        /* i-1 to remove last '.' */
        qname[i-1]='\0';
        printf("qname: %s\n", qname);

        /* QTYPE */
        index=index+2;
        qtype = packet[index];
        /* QCLASS */
        index=index+2;
        qclass = packet[index];
        printf("qtype: %d qclass: %d \n", qtype, qclass);
        index++;
        qdcount--;
    }

    /* Print answer section */
    /* -------------------- */
    printf("*** Answer section:\n");
    while (ancount>0) {

        print_rr(packet, &index);
        ancount--;
    }

    /* Print authority section */
    /* -------------------- */
    printf("*** Authority section:\n");
    while (nscount>0) {

        print_rr(packet, &index);
        nscount--;
    }

    /* Print additional section */
    /* ------------------------ */
    printf("*** Additional section:\n");
    while (arcount>0) {

        print_rr(packet, &index);
        arcount--;
    }

    printf("==============================\n");
}

/*
 * Debug function. Print packet in hex.
 */
void dump_hex(char * packet, int size) {

    for (int i=0; i<size; i++) {
        printf(" %02x ", packet[i]);
        if ((i+1)%8==0) printf("\n");
    }
    printf("\n");
}

// ============================================================
//             GET INDEX FUNCTIONS (private functions)
// ============================================================

/*
 *  Return index of question section (always 12)
 */
int packet_question_index() {

    return QUESTION_INDEX;
}

/*
 *  Return index of answer section in DNS packet
 */
int packet_answer_index(char * packet) {

    uint8_t num_question = packet[QDCOUNT];
    int i = packet_question_index();
    // Question = QNAME + QTYPE (2B) + QCLASS (2B)
    while (num_question > 0) {
        // name ends with a O byte
        while (packet[i]!=0) {
            i++;
        }
        i = i + 4 + 1; // index on next record
        num_question--;
    }
    return i;
}

/*
 *  Return index of authority section in DNS packet
 */
int packet_authority_index(char * packet) {

    int num_answer = packet[ANCOUNT];
    int i = packet_answer_index(packet);

    // RR: NAME + TYPE + CLASS + TTL + RDLENGTH + RDATA
    //     dyn  +  2B  +  2B   + 4B  +    2B    +  RDLENGTH

    while (num_answer > 0) {

        // TODO. there might be a bug here!
        // is there name compression in answer section?
        // if so, name doen't end with a 0...
        while (packet[i]!=0) {
            i++;
        }
        i = i + 10; // index on RDLENGTH
        i = i + packet[i] + 1; // index on next record
        num_answer--;
    }
    return i;
}

/*
 *  Return index of additional section in DNS packet
 */
int packet_additional_index(char * packet) {

    int num_authority = packet[NSCOUNT];
    int i = packet_authority_index(packet);

    // RR: NAME + TYPE + CLASS + TTL + RDLENGTH + RDATA
    //     dyn  +  2B  +  2B   + 4B  +    2B    +  RDLENGTH

    while (num_authority > 0) {

        // name ends with a 'O'
        // TODO. we don't support name compression yet.
        while (packet[i]!=0) {
            i++;
        }
        i = i + 10; // index on RDLENGTH
        i = i + packet[i] + 1; // index on next record
        num_authority--;
    }
    return i;
}


// ============================================================
// ============================================================

// ============================================================
//         EXTRACT DATA FROM DNS MESSAGE
// ============================================================

/*
 * Return the number of answers in DNS packet
 */
int count_answer(char * packet) {

     return packet[ANCOUNT];
}

/*
 * Return packet's RCODE (0 no error, 3 name error)
 */
int no_such_name(char * packet) {

    // Read RCODE
    return (packet[3] & 15); // 15 = 0000 1111
}

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
int qname_from_question(char * packet, int size, char * name) {

    /* TODO: check if it's a DNS query packet... */

    /* HEADER:    packet[0]  --> packet[11]  (12 bytes) */
    /* QUESTION:  packet[12] --> ... */

    /* QNAME */
    int i=packet_question_index();
    int j=0, index=0, label_len;

    while ( packet[i]!=0 && (i<size) ) {

        label_len = packet[i++];
        for (j=0; j<label_len; j++) {
            name[index++] = packet[i++];
        }
        name[index++] = '.';
    }

    if (i==size) return -1;

    /* make qname a string */
    /* index-1 to remove last '.' */
    name[index-1]='\0';

    // printf("qname: %s\n", name);
    return 1;
}

/*
 * Extract IP address (4 bytes array) from DNS answer section
 * (we suppose here only one answer)
 */
void ip_from_answer(char * packet, unsigned char ipv4_addr[4]) {

    int i = packet_answer_index(packet);

    // RR: NAME + TYPE + CLASS + TTL + RDLENGTH + RDATA
    //     dyn  +  2B  +  2B   + 4B  +    2B    +  RDLENGTH

    // TODO we should check the name format...
    // but in an answer we know that we use name compression (cf. build_dns_answer fct)
    /*
       The pointer takes the form of a two octet sequence:
      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
      | 1  1|                OFFSET                   |
      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    */

    i=i+12; // index on ip address
    memcpy(ipv4_addr, &packet[i], 4);
}

/*
 * Extract IP address (4 bytes array) from DNS additionnal section
 * (we suppose here only one additionnal section)
 */
void ns_ip_from_add_section(char * packet, unsigned char ipv4_addr[4]) {

    int i = packet_additional_index(packet);

    // RR: NAME + TYPE + CLASS + TTL + RDLENGTH + RDATA
    //     dyn  +  2B  +  2B   + 4B  +    2B    +  RDLENGTH

    // TODO we should check the name format...
    // but in additionnal section we don't support name compression yet.
    // thus full name ends with a 'O'

    while (packet[i]!=0) {
        i++;
    }
    i=i+10; // index on RDLENGTH (should be 4!)
    // printf("ns_ip_from_add_section() fct -- RDLENGTH = %d\n", packet[i]);
    memcpy(ipv4_addr, &packet[++i], 4);
}


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
int build_dns_answer(char * packet, unsigned char ipv4_addr[4])  {

    /* set reply bit */
    /* QR code <-- 1 (response)  */
    /* Bitwise OR */
    packet[2] = packet[2] | 128;

    /* ANCOUNT <-- 1 (number of resource records in the answer section) */
    packet[ANCOUNT-1] = 0;
    packet[ANCOUNT]   = 1;
     /* NSCOUNT <-- 0 (number of resource records in the authority records section) */
    packet[NSCOUNT-1] = 0;
    packet[NSCOUNT]   = 0;
    /* ARCOUNT <-- 0 (number of resource records in the additional records section) */
    packet[ARCOUNT-1] = 0;
    packet[ARCOUNT]   = 0;

    /* ANSWER section = 2 (Name pointer) + 2 (A) + 2 (IN) + 4 (ttl) + 2 (ip len) + 4 (ip)
                      = 16 bytes */

    /* set ANSWER RR */
    int answer_index = packet_answer_index(packet);
    // printf("answer index : %d\n", answer_index);

    /* name */
    /* pointer to qname (cf. message compression)
       The pointer takes the form of a two octet sequence:
      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
      | 1  1|                OFFSET                   |
      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
      OFFSET = Header = 12 bytes
    */
    packet[answer_index++] = (unsigned char) 192; // 0xC0
    packet[answer_index++] = QUESTION_INDEX;  // offset 0x0C

    /* type (2B) = A (1) */
    packet[answer_index++] = 0;
    packet[answer_index++] = 1;

    /* class (2B) = IN (1) */
    packet[answer_index++] = 0;
    packet[answer_index++] = 1;

    /* ttl (4B) = 120sec */
    // TODO. we should read this value from RR file...
    packet[answer_index++] = 0;
    packet[answer_index++] = 0;
    packet[answer_index++] = 0;
    packet[answer_index++] = 120;

    /* data len (2B) = 4 bytes */
    packet[answer_index++] = 0;
    packet[answer_index++] = 4;

    /* addr */
    memcpy(&packet[answer_index], ipv4_addr, 4);

    return answer_index+4;
}

/*
 * Encode domain name (string) as a sequence of labels ending with a zero octet
 * Example: www.test.fr --> 3www4test2fr0
 *
 * Parameters:
 *   domain_name -- the string domain name to convert
 *   encoded_name -- the resulting sequence of labels
 *   size --  the size of the encoded name
 */
void encode_domain_name_string(char * domain_name, char * encoded_name, int * size) {

    char * label;
    int i=0;
    uint8_t l_size;
    char domain_cp[64];

    /* copy string since strtok() function breaks the string */
    strcpy(domain_cp, domain_name);

    /* get the first token */
    label = strtok(domain_cp, ".");
    do {
        // printf("%s\n", label);
        l_size = strlen(label);
        encoded_name[i++] = l_size;
        for (int j=0; j<l_size ; j++) {
            encoded_name[i++] = label[j];
        }
        /* walk through other tokens */
        label = strtok(NULL, ".");
    } while (label != NULL);
    /* end with zero byte */
    encoded_name[i++] = 0;
    *size = i;
}


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
int build_dns_additional(char * packet, char * sub_domain, char * ns, unsigned char ns_ip_addr[4]) {

    /* set reply bit */
    /* QR code <-- 1 (response)  */
    /* Bitwise OR */
    packet[2] = packet[2] | 128;

    /* NSCOUNT <-- 1 (number of resource records in the authority records section) */
    packet[NSCOUNT-1] = 0;
    packet[NSCOUNT]   = 1;
    /* ARCOUNT <-- 1 (number of resource records in the additional records section) */
    packet[ARCOUNT-1] = 0;
    packet[ARCOUNT]   = 1;

    /* index on authoritative secion */
    int index = packet_authority_index(packet);

    // authority section
    //--------------------

    /* name --> sub_domain */
    char encoded_name[64];
    int  encoded_name_size = 0;
    encode_domain_name_string(sub_domain, encoded_name, &encoded_name_size);
    memcpy(&packet[index], encoded_name, encoded_name_size);

    index = index + encoded_name_size;

     /* type (2B) = NS (2) */
    packet[index++] = 0;
    packet[index++] = 2;

    /* class (2B) = IN (1) */
    packet[index++] = 0;
    packet[index++] = 1;

    /* ttl (4B) = 120sec */
    packet[index++] = 0;
    packet[index++] = 0;
    packet[index++] = 0;
    packet[index++] = 120;

    /* rr data */
    encode_domain_name_string(ns, encoded_name, &encoded_name_size);

    /* data len (2B)  */
    packet[index++] = 0;
    packet[index++] = encoded_name_size;

    memcpy(&packet[index], encoded_name, encoded_name_size);

    index += encoded_name_size;

    // additional section
    //--------------------

    /* name -> ns */
    memcpy(&packet[index], encoded_name, encoded_name_size);

    index = index + encoded_name_size;

     /* type (2B) = A (1) */
    packet[index++] = 0;
    packet[index++] = 1;

    /* class (2B) = IN (1) */
    packet[index++] = 0;
    packet[index++] = 1;

    /* ttl (4B) = 120sec */
    packet[index++] = 0;
    packet[index++] = 0;
    packet[index++] = 0;
    packet[index++] = 120;

    /* data len (2B)  */
    packet[index++] = 0;
    packet[index++] = 4;

    memcpy(&packet[index], ns_ip_addr, 4);

    index += 4;
    return(index);
}

/*
 * Create a DNS reply name error packet
 *
 * Parameters:
 *   packet -- the packet used to build the reply
 */
void build_dns_reply_name_error(char * packet) {

    /* set reply bit */
    /* QR code <-- 1 (response)  */
    /* Bitwise OR */
    packet[2] = packet[2] | 128;

    /* ANCOUNT <-- 0 (number of resource records in the answer section) */
    packet[7] = 0;

    /* RCODE = 3 = name error */
    packet[3] = 3;
}

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
int build_dns_request(char * message, char * name) {

    // init everything to 0
    memset(message, 0, 1024); // we know that BUF SIZE is 1024

    // HEADER
    // -------
    // random id
    srand(time(NULL));
    message[0] = (unsigned char) rand() % 255;
    message[1] = (unsigned char) rand() % 255;
    // printf("%x %x\n", message[0], message[1]);

    // Standard query (QR=0, OPCODE=0)
    // Recursion desired (RD=1)
    message[2] = 1; // 0000 0001
    // RA = Z = RCODE = 0
    // 1 Question
    message[4] = 0;
    message[5] = 1;

    // QUESTION
    // ---------
    int i = 12; // header size = 12 (0 to 11)

    // QNAME
    char encoded_name[255];
    int encoded_name_size;
    encode_domain_name_string(name, encoded_name, & encoded_name_size);
    memcpy(&message[i], encoded_name, encoded_name_size);
    i += encoded_name_size;

    // QTYPE = A (0x0001)
    message[i++] = 0;
    message[i++] = 1;

    // QCLASS = IN (0x0001)
    message[i++] = 0;
    message[i++] = 1;

    return i;
}
