SRC = ./unix/

mkbin:
	mkdir -p ../bin

stream_client: mkbin
	gcc -g $(SRC)stream_socket_client.c -o ../bin/stream_client

stream_server: mkbin
	gcc -g $(SRC)stream_socket_server.c -o ../bin/stream_server

all_stream: stream_client stream_server

datagram_client: mkbin
	gcc -g $(SRC)datagram_socket_client.c -o ../bin/datagram_client

datagram_server: mkbin
	gcc -g $(SRC)datagram_socket_server.c -o ../bin/datagram_server

all_datagram: datagram_client datagram_server