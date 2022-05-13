//
// Created by Bridge Strong on 12.05.2022.
//

#include "Server.hpp"

Server::Server(int port, int typeNet, int typeServer):_port(port), _typeNet(typeNet), _typeServer(typeServer) {
	if ((this->_socket = socket(typeNet, typeServer, 0) < 0)){
		throw SocketException();
	}
	memset((char *)&this->_tcpServer, 0, sizeof(_tcpServer));
	this->_tcpServer.sin_port = htons(_port);
	//this->_tcpServer.sin_addr.s_addr = INADDR_ANY;
	this->_tcpServer.sin_family = AF_INET;

	if (bind(this->_socket, (struct sockaddr*)&this->_tcpServer, sizeof (_tcpServer)) < 0) {
		std::cerr << errno << std::endl;
		throw BindPortException();
	}
}


Server::Server(const Server &obj):_port(obj._port), _typeNet(obj._typeNet), _typeServer(obj._typeServer) {
	if (this == &obj){
		throw std::runtime_error("Error copy constructor");
	}

}

void Server::startListen() {
	if (listen(this->_socket, SOMAXCONN) < 0) {
		throw SocketException();
	}
	if ((this->_socketClient = accept(this->_socket, nullptr, nullptr)) < 0) {
		throw SocketException();
	}
}


Server::~Server() {
	close(this->_socket);
}

Server::SocketException(){
	this->_msg = "Exception Socket: error is unknown";
}

Server::SocketException(std::string msg){
	this->_msg = "Exception Socket: " + msg;
}

const char *Server::SocketException::what() const throw() {
	return this->_msg.c_str();
}

const char *Server::BindPortException::what() const throw() {
	return "Failed to bind to port";
}

void Server::serverWait() {
	long result = recv(this->_socketClient, buf, MAX_CLIENT_BUF_SIZE, 0);
	std::stringstream response, response_body;
	if (result < 0) {
		throw SocketException();
	} else if (!result) {
		std::cerr << "Connection is closed.." << std::endl;
	} else {
		buf[result] = 0;
		response_body	<< "<title>Test C++ HTTP Server</title>\n"
						 << "<h1>Test page</h1>\n"
						 << "<p>This is body of the test page...</p>\n"
						 << "<h2>Request headers </h2>\n"
						 << "<pre>" << buf << "</pre>\n"
						 << "<em><small>Test C++ Http Server</small></em>\n";
		response 	<< "HTTP/1.1 200 OK\r\n"
					<< "Version: HTTP/1.1\r\n"
					<< "Content-Type: text/html; charset=utf-8\r\n"
					<< "Content-Length: " << response_body.str().length()
					<< "\r\n\r\n"
					<< response_body.str();
		result = send(this->_socketClient, response.str().c_str(), response.str().length(), 0);
		if (result < 0) {
			std::cerr << "Send failed" << std::endl;
		}
	}
}


//TODO:

/*
**	server must be singletone?
**	test with struct addrinfo* addr; + struct addrinfo hints;
**	copy exception from socket to bind
*/
