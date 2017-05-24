#ifndef _SNAKE_CONNECTION_
#define _SNAKE_CONNECTION_

#include <chrono>
#include <deque>
#include <list>

#include "session.h"
#include "map.h"

class Connection {
 public:
  using TimePoint = std::chrono::steady_clock::time_point;
  using ListType = std::list<std::pair<Map, TimePoint> >;
  
  Connection() = default;
  Connection(const std::string &ip_address);
  
  Connection(const Connection &) = delete;
  Connection(Connection &&) = default;
  
  Connection &operator=(const Connection &) = delete;
  Connection &operator=(Connection &&) = default;
  
  virtual ~Connection() = default;

  virtual void ConnectToServer(const std::string &ip_address);

  virtual std::chrono::milliseconds SendMap(const Map &);

  virtual std::chrono::milliseconds ReceiveMaps(ListType &);

  virtual int Disconnect();
  
 private:
  network::Session session_;
  std::deque<char> buff_;
};

#endif // _SNAKE_CONNECTION_
