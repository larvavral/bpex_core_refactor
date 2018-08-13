#ifndef REDIS_REDIS_CLIENT_H_
#define REDIS_REDIS_CLIENT_H_

#include <string>

#include "hiredis/hiredis.h"

namespace redis {

// Simple C++ wrapper for Hiredis normal client, which used synchronous API.
class RedisClient {
public:
  RedisClient(const std::string& host, int port);
  ~RedisClient();

  // Connect to redis server.
  void Connect();

  // Check whether redis client is connected or not.
  bool IsConnected();

  // Authenticate in case password is required.
  bool Authenticate(const std::string& password);

  // GET command.
  std::string Get(const std::string& key);

  // SET command.
  void Set(const std::string& key, const std::string& value);

  const std::string& host() { return host_; }
  int port() { return port_; }

private:
  std::string host_;
  int port_;

  redisContext* context_;
};

} // namespace redis

#endif  // REDIS_REDIS_CLIENT_H_