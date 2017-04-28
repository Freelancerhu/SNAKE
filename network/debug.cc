
#include "tcp.h"

#include <cassert>

#include <iostream>

void ClientServerExemple();
void RequestGoogleMainPage();

int main() {
  ClientServerExemple();
  
  return 0;
}

void ClientServerExemple() {
  try {
    network::TcpSocket server, client;
    
    if (server.Listen("127.0.0.1", 15263))
      throw std::runtime_error("Listen " + server.GetLastError());
    if (client.Connect("127.0.0.1", 15263))
      throw std::runtime_error("Connect " + client.GetLastError());
    
    auto new_connection = server.Accept();
    if(!new_connection)
      throw std::runtime_error("Accept " + server.GetLastError());
    
    int n = client.Write("Hello, World!");
    if (n < 0)
      throw std::runtime_error("Write " + new_connection.GetLastError());
    
    std::cout << n << " byte(s) written" << std::endl;
    
    char buff2[1024];
    n = new_connection.Read(std::begin(buff2), std::end(buff2));
    if (n < 0)
      throw std::runtime_error("Read " + new_connection.GetLastError());
    std::cout << n << " byte(s) read" << std::endl;
    std::cout.write(buff2, n);
    std::cout << std::endl;
    
  } catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void RequestGoogleMainPage() {
  try {
    network::TcpSocket socket;
    
    char header[] = "\
GET / HTTP/1.1\r\n\
Host: www.google.com\r\n\
Accept: text/html;\r\n\
Accept-Language: en-us,en;\r\n\
Accept-Charset: utf-8;\r\n\
Connection: close\r\n\
Cache-Control: no-cache;\r\n\r\n";

    if (socket.Connect("74.125.206.103", 80))
      throw std::runtime_error("Connect " + socket.GetLastError());
    
    char buff[1024];
    int n = 0;
    
    char *p = header;
    while ((n=socket.Write(p, std::end(header)-1)) > 0)
      p+=n;
    
    while((n=socket.Read(std::begin(buff), std::end(buff),
                         std::chrono::seconds(1))) > 0) {
      std::cout.write(buff, n);
    }
    
    if (n < 0)
      throw std::runtime_error(socket.GetLastError());
    
  } catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}