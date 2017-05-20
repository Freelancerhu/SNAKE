
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <thread>

#include "tcp.h"

using network::TcpSocket;

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
  
  int Read(char *sink, int n, std::chrono::milliseconds &time_out) {
    auto start = std::chrono::steady_clock::now();
    int count = 0;
    for (;;) {
      if (count == n)
        break;
      
      int byte_read = socket_.ReadAByte(time_out);
      
      if (byte_read == std::char_traits<char>::eof())
        break;
      
      sink[count++] = byte_read;
      if ((std::chrono::steady_clock::now() - start) >= time_out)
        break;
    }
    
    time_out -= std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    return count;
  }
  
  std::chrono::milliseconds Write(const char *source, int n) {
    auto start = std::chrono::steady_clock::now();
    const int total_bytes = n;
    int bytes_writen = 0;
    while (bytes_writen < total_bytes) {
      std::cerr << "!!" << source + bytes_writen << std::endl;
      int size = socket_.Write(source + bytes_writen, source + total_bytes);
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
  TcpSocket socket;
  socket.Connect("127.0.0.1", 12587);
  
  std::cerr << "connected" << std::endl;
  Session session(std::move(socket));
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