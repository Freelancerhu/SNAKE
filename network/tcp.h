#ifndef _SNAKE_NETWORK_TCP_H_
#define _SNAKE_NETWORK_TCP_H_

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

#include <cassert>
#include <cstring>

#include <chrono>
#include <stdexcept>
#include <utility>

namespace network {
  
struct non_block_t {};
extern non_block_t non_block;

class TcpSocket {
 public:
  friend class NetworkService;
  
  TcpSocket() = default;
  explicit TcpSocket(int file_descriptor) noexcept
      : file_descriptor_(file_descriptor) {}
  
  TcpSocket(const TcpSocket &) = delete;
  TcpSocket(TcpSocket &&rhs) noexcept
      : file_descriptor_(rhs.file_descriptor_ ) {
    rhs.file_descriptor_ = -1;
  }
  
  ~TcpSocket() {
    Close();
  }
  
  TcpSocket &operator=(const TcpSocket &) = delete;
  TcpSocket &operator=(TcpSocket &&rhs) noexcept {
    file_descriptor_ = rhs.file_descriptor_;
    rhs.file_descriptor_ = -1;
  }
  
  int Listen(const std::string &address, uint16_t port) {
    sockaddr_in addr{AF_INET, htons(port)};
    if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) != 1)
      throw std::runtime_error("inet_pton failed with: " + address + __func__);
    
    int ret = bind(file_descriptor_, (sockaddr *)&addr, sizeof(sockaddr_in));
    if (ret != 0)
      return ret;
    return listen(file_descriptor_, port);
  }
  
  int Connect(const std::string &address, uint16_t port) {
    sockaddr_in addr{AF_INET, htons(port)};
    if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) != 1)
      throw std::runtime_error("inet_pton failed with: " + address + __func__);
    
    return connect(file_descriptor_, (sockaddr *)&addr, sizeof(sockaddr_in));
  }
  template <class Rep, class Period>
  int Connect(const std::string &address, uint16_t port,
              const std::chrono::duration<Rep, Period> &duration) {
    assert(duration.count() >= 0);
    return Connect(address, port,
                   static_cast<std::chrono::milliseconds>(duration).count());
  }
  
  std::pair<TcpSocket, int> Accept() {
    auto ret = accept(file_descriptor_, nullptr, nullptr);
    return {TcpSocket(ret), ret};
  }
  template <class Rep, class Period>
  std::pair<TcpSocket, int> Accept(
      const std::chrono::duration<Rep, Period> &duration) {
    assert(duration.count() >= 0);
    return Accept(static_cast<std::chrono::milliseconds>(duration).count());
  }
  
  int Read(char *first, char *last) {
    assert(first<=last);
    return read(file_descriptor_, first, last-first);
  }
  int Write(const char *first, const char *last) {
    assert(first<=last);
    return write(file_descriptor_, first, last-first);
  }
  template <size_t N>
  int Write(const char (&buff)[N]) {
    return Write(buff, buff+N);
  }

  template <class Rep, class Period>
  int Read(char *first, char *last,
           const std::chrono::duration<Rep, Period> &duration) {
    assert(first<=last);
    assert(duration.count() > 0);
    return Read(first, last,
                static_cast<std::chrono::milliseconds>(duration).count());
  }
  template <class Rep, class Period>
  int Write(const char *first, const char *last,
            const std::chrono::duration<Rep, Period> &duration) {
    assert(first<=last);
    assert(duration.count() > 0);
    return Write(first, last,
                 static_cast<std::chrono::milliseconds>(duration).count());
  }
  
  int Close() {
    return close(file_descriptor_);
  }
  
  std::string GetLastError() const {
    return strerror(errno);
  }
  
 private:
  std::pair<TcpSocket, int> Accept(uint64_t milliseconds);
  int Connect(const std::string &address, uint16_t port, uint64_t milliseconds);
  int Read(char *first, char *last, uint64_t milliseconds);
  int Write(const char *first, const char *last, uint64_t milliseconds);
  
  int GetLocalHandler() const {
    return file_descriptor_;
  }

  int file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
};

} // namespace network

#endif // _SNAKE_NETWORK_TCP_H_