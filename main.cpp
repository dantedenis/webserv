#include <iostream>
#include <sys/socket.h>

#include "Server.hpp"

#define PORT 4242

int main() {
	try {
		Server server(PORT, AF_INET, SOCK_STREAM);
		server.startListen();
		while (true){
			server.serverWait();
		}
	} catch (std::exception &ex){
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}
