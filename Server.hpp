//
// Created by Bridge Strong on 12.05.2022.
//

#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP

#include <exception>
#include <iostream>
#include <sys/socket.h>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>

class Server {
private:
	const int			_port;
	const int			_typeNet;
	const int 			_typeServer;
	int 				_socket;
	int 				_socketClient;
	struct sockaddr_in	_tcpServer;
	static const int	MAX_CLIENT_BUF_SIZE = 1024;
	char				buf[MAX_CLIENT_BUF_SIZE];
	Server& operator=(const Server&);
	//Server(){};
public:
	Server(int port, int typeNet, int typeServer);
	Server(const Server&);
	~Server();
	void startListen();
	void serverWait();

	class SocketException: public std::exception {
	public:
		virtual const char *what() const throw();
	};

	class BindPortException: public std::exception {
	public:
		virtual const char *what() const throw();
	};

};


#endif //WEBSERV_SERVER_HPP
