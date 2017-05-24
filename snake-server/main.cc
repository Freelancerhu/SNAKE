
#include <signal.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>

#include "session.h"
#include "tcp.h"

bool Check(const char *first, const char *last) {
  static const char token[] = "SNAKESNAKE";
  static_assert(sizeof(token)>=10, "");
  return std::equal(first, last, token, token+10);
}

class ServerSession : public network::Session {
 public:
  using Session::Session;
  using Session::AdaptSocket;
  using Session::Read;
  using Session::Write;
  
  bool IsValid() {
    char buff[10];
    std::chrono::milliseconds time_out(3000);
    
    int n = Read(buff, 10, time_out);
    return Check(buff, buff+n);
  }
};

int main() {
  signal(SIGPIPE, SIG_IGN);
  
  network::TcpSocket server;
  
  server.Listen("127.0.0.1", 12500);
  char buff[10240];
  
  for (;;) {
    try {
      std::cerr << "Waiting" << std::endl;
      ServerSession session_a(server.Accept());
      std::cerr << "1 Connected" << std::endl;
      if (session_a.IsValid() == false)
        continue;
      std::cerr << "1 Valid" << std::endl;
      
      ServerSession session_b;
      for (;;) {
        network::TcpSocket socket = server.Accept();
        std::cerr << "2 Connected" << std::endl;
        session_b.AdaptSocket(std::move(socket));
        if (session_b.IsValid()) {
          std::cerr << "2 Valid" << std::endl;
          break;
        }
      }
      
      session_a.Write("Hello", 5);
      session_b.Write("Hello", 5);

      for (;;) {
        auto time_out = std::chrono::milliseconds(10);
        int n = session_a.Read(buff, 10240, time_out);
        session_b.Write(buff, n);

        time_out = std::chrono::milliseconds(10);
        n = session_b.Read(buff, 10240, time_out);
        session_a.Write(buff, n);
      }
    } catch(std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  return 0;
}
