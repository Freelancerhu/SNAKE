
#include "connection.h"

#include <algorithm>
#include <iterator>

#include "tcp.h"

void Connection::ConnectToServer(const std::string &ip_address) {
  network::TcpSocket socket;
  if (socket.Connect(ip_address, 12500))
    throw std::runtime_error("Cannot connect to server");
  session_.AdaptSocket(std::move(socket));
  session_.Write("SNAKESNAKE", 10);
}

std::chrono::milliseconds Connection::SendMap(const Map &map) {
  std::string str = map.Serialize();
  return session_.Write(str.c_str(), str.length() + 1);
}

std::chrono::milliseconds Connection::ReceiveMaps(ListType &list) {
  auto start = std::chrono::steady_clock::now();
  
  char buff[1024];
  int n = 0;
  std::chrono::milliseconds time_out = std::chrono::milliseconds(0);
  while ((n = session_.Read(buff, 1024, time_out)) != 0)
    buff_.insert(buff_.end(), buff, buff+n);
  
  while (list.size()>1)
    list.pop_front();
  
  for (;;) {
    auto first = std::find(buff_.begin(), buff_.end(), 'M');
    if (first != buff_.end()) {
      Map map;
      auto last = std::find(std::next(first), buff_.end(), 'E');
      if (last == buff_.end())
        break;
      
      std::string str(first, last);
      map.Deserialize(str);
      
      list.emplace_back(std::make_pair(
          std::move(map), std::chrono::steady_clock::now()));
      
      if (last != buff_.end())
        std::advance(last, 1);
      buff_.erase(buff_.begin(), last);
    } else {
      break;
    }
  }
  
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - start);
}

int Connection::Disconnect() {
  return session_.Close();
}
