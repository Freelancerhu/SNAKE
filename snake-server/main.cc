
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>

#include "tcp.h"

using network::TcpSocket;

bool Check(TcpSocket &socket) {
  char buff[10], *p = buff;
  while (p!=std::end(buff))
    if (socket.Read(p, std::end(buff), std::chrono::seconds(3)) <= 0)
      return false;
  
  static const char token[] = "SNAKESNAKE";
  static_assert(sizeof(token)>=10, "");
  return std::equal(buff, std::end(buff), token, token+10);
}

int main() {
  TcpSocket server;
  std::list<TcpSocket> peers;
  
  if (server.Listen("0.0.0.0", 37458) < 0)
    std::cerr << "Can not listen" << std::endl;
  
  for (;;) {
    while (peers.size() < 2)
      peers.emplace_back(server.Accept());
    
    char buff[1024];
    for (auto ite = peers.begin(); ite != peers.end(); ++ite) {
      auto &peer = *ite;
      auto n = peer.Read(buff, std::end(buff),
          std::chrono::milliseconds(16));
      if (n < 0) {
        peers.erase(ite);
      } else {
        for (auto ite = peers.begin(); ite != peers.end(); ++ite) {
          auto &peer = *ite;
          peer.Write(buff, buff+n);
        }
      }
    }
    
  }
  
  return 0;
}