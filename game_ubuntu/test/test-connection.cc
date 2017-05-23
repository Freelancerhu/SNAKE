
#include <cassert>

#include <chrono>
#include <thread>

#define private public

#include "connection.h"
#include "map"

#include "tcp.h"

int main() {
  Connection c1, c2;
  
  network::TcpSocket socket;
  if(socket.Listen("127.0.0.1", 12500))
    throw std::runtime_error("Listen error");

  {
    std::cout << "Connecting" << std::endl;
    c1.ConnectToServer("127.0.0.1");
    auto peer = socket.Accept();
    c2.session_.AdaptSocket(std::move(peer));
  }
  
  Map map;
  map.game_map_.resize(10);
  for (auto &row : map.game_map_)
    row.assign({1,2,3,4,5,6});
  
  Connection::ListType list;
  
  std::cout << "Sending" << std::endl;
  c1.SendMap(map);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  
  std::cout << "Receiving" << std::endl;
  c2.ReceiveMaps(list);
  assert(list.size() == 1);
  auto received_map = list.front().first;
  
  for (auto &row : received_map.game_map_) {
    for (auto ele : row)
      std::cout << ele << " ";
    std::cout << std::endl;
  }
  
  return 0;
}
