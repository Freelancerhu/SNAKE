
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <thread>

#include "session.h"
#include "tcp.h"

bool Check(const char *first, const char *last) {
  static const char token[] = "SNAKESNAKE";
  static_assert(sizeof(token)>=10, "");
  return std::equal(first, last, token, token+10);
}

int main() {
  network::TcpSocket socket;
  socket.Connect("127.0.0.1", 12587);
  
  std::cerr << "connected" << std::endl;
  network::Session session(std::move(socket));
  session.Write("SNAKESNAKE", 10);
  
  std::cerr << "Sending Message" << std::endl;
  for (int i=0; i<100; ++i) {
    auto time = session.Write("A Message", 9);
    
    char buff[128];
    auto time_out = std::chrono::milliseconds(20);
    int n = session.Read(buff, 128, time_out);
    std::cout << n << " ";
    std::cout.write(buff, n);
    std::cout << std::flush;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100) - time);
  }
  
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  
  return 0;
}