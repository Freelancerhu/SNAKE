
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <thread>

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
  TcpSocket socket;

  if (socket.Connect("127.0.0.1", 37458) < 0)
    exit(1);
  
  std::cout << "Connected" << std::endl;
  const char token[] = "SNAKESNAKE";
  socket.Write(token, token+10);
  std::cout << "Token sended" << std::endl;
  
  char buff[1024];
  for (int i=0; i<100; ++i) {
    int n = socket.Read(buff, buff+1024, std::chrono::milliseconds(16));
    if (n >= 0)
      std::cout.write(buff, n);
    std::this_thread::sleep_for(std::chrono::milliseconds(64));
    socket.Write("abcd");
    
    std::cout << "Message sended" << std::endl;
  }
  
  return 0;
}