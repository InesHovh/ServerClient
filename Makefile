CC = g++
CFLAGS = -Wall -std=c++11

all: server client

server: Server.cpp Server.hpp
	$(CC) $(CFLAGS) -o server Server.cpp

client: Client.cpp Client.hpp
	$(CC) $(CFLAGS) -o client Client.cpp

clean:
	rm -f server client


fclean: clean
	rm -f server client

re: fclean all

.PHONY: all clean fclean
