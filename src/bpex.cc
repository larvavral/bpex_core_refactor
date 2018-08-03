#include "bpex.h"

#include "configuration.h"
#include "cpp_redis/cpp_redis"

Bpex::Bpex() {
  Initialize();
}

void Bpex::Initialize() {
  RedisServerInformation redis_server =
      Configuration::GetInstance()->GetRedisServerInfo();

  cpp_redis::client client;
  //client.connect(redis_server.ip,
}