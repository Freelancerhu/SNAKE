
#include "session.h"

namespace network {

int Session::Read(char *sink, int size, std::chrono::milliseconds &time_out) {
  auto start = std::chrono::steady_clock::now();
  int count = 0;
  for (;;) {
    if (count == size)
      break;
    
    int byte_read = socket_.ReadAByte(time_out);
    
    if (byte_read == std::char_traits<char>::eof())
      break;
    
    sink[count++] = byte_read;
    time_out -= std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - start);
    if (time_out.count() <= 0)
      break;
  }

  return count;
}

std::chrono::milliseconds Session::Write(const char *source, int n) {
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

} // namespace network
