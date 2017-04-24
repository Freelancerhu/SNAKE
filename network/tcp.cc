#include "tcp.h"

#include <fcntl.h>
#include <poll.h>

namespace network {
  
non_block_t non_block;

int TcpSocket::Connect(const std::string &address, uint16_t port,
                       uint64_t milliseconds) {
  sockaddr_in addr{AF_INET, htons(port)};
  if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) != 1)
    throw std::runtime_error("inet_pton failed with: " + address + __func__);
  
  const auto flag = fcntl(file_descriptor_, F_GETFL, 0);
  if (flag < 0)
    return flag;
  
  auto ret = fcntl(file_descriptor_, F_SETFL, flag | O_NONBLOCK);
  if (ret < 0)
    return ret;
  
  connect(file_descriptor_, (sockaddr *)&addr, sizeof(sockaddr_in));
  
  pollfd fdarray[1] = {{file_descriptor_, POLLOUT, 0}};
  ret = poll(fdarray, 1, milliseconds);
  if (ret == 1) {
    int so_error;
    socklen_t len = sizeof(so_error);
    
    getsockopt(file_descriptor_, SOL_SOCKET, SO_ERROR, &so_error, &len);
    if (so_error == 0) {
      fcntl(file_descriptor_, F_SETFL, flag);
      return 0;
    }
  }
  
  fcntl(file_descriptor_, F_SETFL, flag);
  close(file_descriptor_);
  return 1;
}

std::pair<TcpSocket, int> TcpSocket::Accept(uint64_t milliseconds) {
  pollfd fdarray[1] = {{file_descriptor_, POLLIN, 0}};
  auto ret = poll(fdarray, 1, milliseconds);
  if (ret <= 0)
    return {TcpSocket(ret), ret};
  
  ret = accept(file_descriptor_, nullptr, nullptr);
  return {TcpSocket(ret), ret};
}

int TcpSocket::Read(char *first, char *last, uint64_t milliseconds) {
  pollfd fdarray[1] = {{file_descriptor_, POLLIN, 0}};
  auto ret = poll(fdarray, 1, milliseconds);
  if (ret <= 0)
    return ret;
  
  return read(file_descriptor_, first, last-first);
}
int TcpSocket::Write(const char *first, const char *last,
                     uint64_t milliseconds) {
  pollfd fdarray[1] = {{file_descriptor_, POLLOUT, 0}};
  auto ret = poll(fdarray, 1, milliseconds);
  if (ret <= 0)
    return ret;
  
  return write(file_descriptor_, first, last-first);
}

} // namespace network