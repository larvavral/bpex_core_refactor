#include "redis/redis_client.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace redis {

RedisClient::RedisClient(
    const std::string& host,
    int port)
    : host_(host),
      port_(port),
      context_(nullptr) {
}

RedisClient::~RedisClient() {
  if (context_) {
    // Disconnect and free the context.
    redisFree(context_);
    context_ = nullptr;
  }
}

void RedisClient::Connect() {
  if (context_)
    return;

  context_ = redisConnect(host_.c_str(), port_);
  if (context_->err) {
#ifdef _DEBUG
    std::cout << "Connect to redis server failed: " << context_->err << std::endl;
#endif

    redisFree(context_);
    context_ = nullptr;
  }
}

bool RedisClient::IsConnected() {
  return (context_ != nullptr);
}

bool RedisClient::Authenticate(const std::string& password) {
  if (!IsConnected())
    return false;

  redisReply* reply = (redisReply*) redisCommand(context_, "AUTH %s", password.c_str());
  bool result = (reply->type != REDIS_REPLY_ERROR);

#ifdef _DEBUG
  if (!result)
    std::cout << "Authenticate failed: " << reply->str << std::endl;
#endif

  freeReplyObject(reply);
  return result;
}

std::string RedisClient::Get(const std::string& key) {
  if (!IsConnected())
    return std::string();

  std::string result;
  redisReply* reply = (redisReply*) redisCommand(context_, "GET %s", key.c_str());
  if (reply->type == REDIS_REPLY_STRING)
    result = reply->str;

  freeReplyObject(reply);
  return result;
}

void RedisClient::Set(const std::string& key, const std::string& value) {
  if (!IsConnected())
    return;

  redisReply* reply =
      (redisReply*) redisCommand(context_, "SET %s %s", key.c_str(), value.c_str());
  freeReplyObject(reply);
}

} // namespace redis
