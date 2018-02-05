FLAGS = -Wall -pedantic -std=c99
CC = gcc

LIBS = dns_server_rr_files.o dns_packet_parsing.o utils.o

dns_client: dns_client.o dns_packet_parsing.o utils.o
	$(CC) $(FLAGS) dns_client.o dns_packet_parsing.o utils.o -o $@

dns_server_v0: $(LIBS) dns_server_v0.o
	$(CC) $(FLAGS) $(LIBS) dns_server_v0.o -o $@

dns_server_v1: $(LIBS) dns_server_v1.o
	$(CC) $(FLAGS) $(LIBS) dns_server_v1.o -o $@

dns_server_local_v1: $(LIBS) dns_server_local.o
	$(CC) $(FLAGS) $(LIBS) dns_server_local.o -o $@

all: dns_client dns_server_v0 dns_server_v1 dns_server_local_v1

test_v1: all
	xterm -e ./dns_server_v1 RR/univ-tlse3.fr.conf 12700 &
	xterm -e ./dns_server_v1 RR/wikipedia.fr.conf 12827 &
	xterm -e ./dns_server_v1 RR/tld.fr.conf 1270 &
	xterm -e ./dns_server_v1 RR/root.conf 8888 &
	xterm -e ./dns_server_local_v1 5300 &

kill_test:
	for p in `pgrep dns_serv`; do kill $$p; done

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency
%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f dns_client dns_server_v0 dns_server_v1 dns_server_local_v1
	rm -f *.o
	rm -rf tmp
