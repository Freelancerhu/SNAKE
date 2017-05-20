
#include <signal.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>

#include "tcp.h"

using network::TcpSocket;

bool Check(const char *first, const char *last) {
  static const char token[] = "SNAKESNAKE";
  static_assert(sizeof(token)>=10, "");
  return std::equal(first, last, token, token+10);
}

class Session {
 public:
  Session() = default;
  
  Session(TcpSocket &&socket) : socket_(std::move(socket)) {}
  
  TcpSocket AdaptSocket(TcpSocket &&socket) {
    socket.Swap(socket_);
    return std::move(socket);
  }
  
  bool IsValid() {
    char buff[10];
    std::chrono::milliseconds time_out(3000);
    
    int n = Read(buff, 10, time_out);
    return Check(buff, buff+n);
  }
  
  int Read(char *s, int size, std::chrono::milliseconds &time_out) {
    auto start = std::chrono::steady_clock::now();
    int count = 0;
    for (;;) {
      if (count == size)
        break;
      
      int byte_read = socket_.ReadAByte(time_out);
      
      if (byte_read == std::char_traits<char>::eof())
        break;
      
      s[count++] = byte_read;
      time_out -= std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
      if (time_out.count() <= 0)
        break;
    }

    return count;
  }
  
  std::chrono::milliseconds Write(const char *source, int n) {
    auto start = std::chrono::steady_clock::now();
    const int total_bytes = n;
    int bytes_writen = 0;
    while (bytes_writen < total_bytes) {
      int size = socket_.Write(source + bytes_writen, source + n);
      if (size < 0)
        throw std::runtime_error("Session write failed");
      bytes_writen += size;
    }
    
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
  }
  
 private:
  TcpSocket socket_;
};


int main() {
  signal(SIGPIPE, SIG_IGN);
  
  TcpSocket server;
  
  server.Listen("127.0.0.1", 12587);
  char buff[10240];
  
  for (;;) {
    try {
      std::cerr << "Waiting" << std::endl;
      Session session_a(server.Accept());
      std::cerr << "1 Connected" << std::endl;
      if (session_a.IsValid() == false)
        continue;
      std::cerr << "1 Valid" << std::endl;
      
      Session session_b;
      for (;;) {
        TcpSocket socket = server.Accept();
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
