
#include <signal.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>

#include "tcp.h"

using network::TcpSocket;

bool Check(TcpSocket &socket) {
  char buff[10], *p = buff;
  while (p!=std::end(buff)) {
    int n = socket.Read(p, std::end(buff), std::chrono::seconds(3));
    if (n <= 0)
      return false;
    p += n;
  }
  
  std::cout << "Token Received" << std::endl;
  static const char token[] = "SNAKESNAKE";
  static_assert(sizeof(token)>=10, "");
  return std::equal(buff, std::end(buff), token, token+10);
}

void Broadcast(std::list<TcpSocket> &peers) {
  std::list<std::list<TcpSocket>::iterator> connection_lost;
  
  char buff[1024];
  for (auto receiver = peers.begin(); receiver != peers.end();
       ++receiver) {
    auto n = receiver->Read(buff, std::end(buff),
        std::chrono::milliseconds(16));
    if (n < 0) {
      connection_lost.emplace_back(receiver);
      std::clog << "Connection lost" << std::endl;
      break;
    } else {
      for (auto sender = peers.begin(); sender != peers.end(); ++sender) {
        if (receiver == sender)
          continue;
        if (sender->Write(buff, buff+n) < 0) {
          connection_lost.emplace_back(sender);
          std::clog << "Connection lost" << std::endl;
        }
      }
    }
  }
  
  auto end = std::unique(connection_lost.begin(), connection_lost.end());
  for (auto ite = connection_lost.begin(); ite!=end; ++ite)
    peers.erase(*ite);
}

int main() {
  signal(SIGPIPE, SIG_IGN);
  
  try {
    TcpSocket server;
    std::list<TcpSocket> peers;
    
    if (server.Listen("127.0.0.1", 37458) < 0)
      std::cerr << "Can not listen" << std::endl;
    
    for (;;) {
      while (peers.size() < 2) {
        std::clog << "Accept new connection" << std::endl;
        peers.emplace_back(server.Accept());
        if (Check(peers.back()) == false) {
          std::clog << "Peer poped" << std::endl;
        } else {
          std::clog << "Peer accepted" << std::endl;
        }
      }

      Broadcast(peers);
    }
    
    std::clog << "Server ended" << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  
  std::clog << "exited" << std::endl;
  return 0;
}