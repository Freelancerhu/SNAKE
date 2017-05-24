
#include <cassert>

#include <chrono>
#include <thread>

#define private public

#include "connection.h"
#include "map"

#include "tcp.h"

int main() {
  network::TcpSocket socket;
  if (socket.Listen("127.0.0.1", 12500))
    throw std::runtime_error("Listen failed!");
  
  auto peer = socket.Accept();
  
  if (!peer)
    throw std::runtime_error("Accept failed!");
  
  Connection connection;
  connection.session_.AdaptSocket(std::move(peer));
  
  Map map[2];
  map[0].game_map_.resize(20);
  for (auto &row : map[0].game_map_) {
    row.resize(20);
    for (auto &ele : row) {
      ele = 2;
    }
  }
  
  map[1].game_map_.resize(20);
  for (auto &row : map[1].game_map_) {
    row.resize(20);
    for (auto &ele : row) {
      ele = 1;
    }
  }
  
  int k = 0;
  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    connection.SendMap(map[k++%2]);
    
    Connection::ListType list;
    connection.ReceiveMaps(list);
    
    auto received_map = list.front().first;
  
    for (auto &row : received_map.game_map_) {
      for (auto ele : row)
        std::cout << ele << " ";
      std::cout << std::endl;
    }
  }
  
  return 0;
}