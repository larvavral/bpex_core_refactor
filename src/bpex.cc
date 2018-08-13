#include "bpex.h"

#include "configuration.h"
#include "redis/async_connection.h"
#include "redis/redis_client.h"

#ifdef _DEBUG
#include <iostream>
#endif

void foo(redisAsyncContext* ac, void* reply, void* privdata) {
  std::cout << "Larva 1: hahah" << std::endl;
}

void bar(int status) {
  std::cout << "Connected" << std::endl;
}

Bpex::Bpex() {
  Initialize();
}

void Bpex::Initialize() {
  RedisServerInformation redis_server =
      Configuration::GetInstance()->GetRedisServerInfo();

#ifdef _DEBUG
  std::cout << "Redis server: "
            << redis_server.ip << " "
            << redis_server.port << " "
            << redis_server.password << std::endl;
#endif

  // redis::RedisClient redis_client(redis_server.ip, redis_server.port);
  // redis_client.Connect();
  // redis_client.Authenticate(redis_server.password);

  // redis_client.Set("hoangpq", "hahaha");

  redis::AsyncConnection async_con(redis_server.ip, redis_server.port);
  async_con.SetOnConnectedCallback(bar);

  async_con.Connect();
  std::string cmd = "AUTH " + redis_server.password;
  async_con.ExecuteAsyncCommand(cmd, std::bind(&Bpex::Test, this, std::placeholders::_1, 3));

  redisAsyncCommand(async_con.async_context_, foo, (void*)1, "AUTH %s", redis_server.password.c_str());
}

void Bpex::Test(redisReply* reply, int i) {
  std::cout << "OK " << i << std::endl;
  std::cout << "Larva: " << reply->type << std::endl;
}

