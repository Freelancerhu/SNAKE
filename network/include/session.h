#ifndef _NETWORK_SESSION_H_
#define _NETWORK_SESSION_H_

#include <chrono>
#include <utility>

#include "tcp.h"

namespace network {

class Session {
 public:
  Session() = default;
  Session(TcpSocket &&socket) : socket_(std::move(socket)) {}
  
  Session(const Session &) = delete;
  Session(Session &&) = default;
  
  Session &operator=(const Session &) = delete;
  Session &operator=(Session &&) = default;
  
  virtual ~Session() = default;
  
  virtual TcpSocket AdaptSocket(TcpSocket &&socket) {
    socket.Swap(socket_);
    return std::move(socket);
  }
  
  virtual int Read(char *sink, int size, std::chrono::milliseconds &time_out);
  
  virtual std::chrono::milliseconds Write(const char *source, int n);
  
 private:
  TcpSocket socket_;
};

} // namespace network

#endif // _NETWORK_SESSION_H_
