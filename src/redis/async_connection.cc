#include "redis/async_connection.h"

#ifdef _DEBUG
#include <iostream>
#endif

extern struct event_base *base;

namespace redis {

AsyncConnection::AsyncConnection(const std::string& host, int port)
    : host_(host),
      port_(port),
      async_context_(nullptr),
      on_connected_callback_(nullptr),
      on_disconnected_callback_(nullptr) {
}

AsyncConnection::~AsyncConnection() {
  if (IsConnected())
    Disconnect();
}

void AsyncConnection::Connect() {
  //struct event_base *base = event_base_new();

  async_context_ = redisAsyncConnect(host_.c_str(), port_);
  // |redisAsyncContext::data| is not used by hiredis, so we used this field to
  // callback when event come.
  async_context_->data = (void*) this;
  if (async_context_->err) {
#ifdef _DEBUG
    std::cout << "Create async connection failed: " << async_context_->err << std::endl;
#endif

    async_context_ = nullptr;
    return;
  }

  redisLibeventAttach(async_context_, base);
  redisAsyncSetConnectCallback(async_context_, &AsyncConnection::Connected);
  redisAsyncSetDisconnectCallback(async_context_, &AsyncConnection::Disconnected);
  //event_base_dispatch(base);
  std::cout << "OK" << std::endl;
}

bool AsyncConnection::IsConnected() {
  return (async_context_ != nullptr);
}

void AsyncConnection::Disconnect() {
  if (async_context_) {
    redisAsyncDisconnect(async_context_);
    async_context_ = nullptr;
  }
}

// static
void AsyncConnection::Connected(const redisAsyncContext* ac, int status) {
  if (ac && ac->data)
    ((AsyncConnection*)(ac->data))->OnConnected(status);
}

// static
void AsyncConnection::Disconnected(const redisAsyncContext* ac, int status) {
  if (ac && ac->data)
    ((AsyncConnection*)(ac->data))->OnDisconnected(status);
}

// void Authenticate(const std::string& password) {
//   std::string cmd = "AUTH " + password;
//   ExecuteAsyncCommand(
//       cmd,
//       std::bind(&AsyncConnection::OnAuthenticated, this, std::placeholders::_1));
// }

void AsyncConnection::OnConnected(int status) {
#ifdef _DEBUG
  std::cout << "AsyncConnection: Connected to redis server" << std::endl;
#endif

  if (status != REDIS_OK) {
#ifdef _DEBUG
    std::cout << "Connect to redis server failed" << std::endl;
#endif
    async_context_ = nullptr;
  }

  if (on_connected_callback_)
    on_connected_callback_(status);
}

void AsyncConnection::OnDisconnected(int status) {
#ifdef _DEBUG
  std::cout << "AsyncConnection: Disconnected to redis server" << std::endl;
#endif

  if (status != REDIS_OK) {
    async_context_ = nullptr;
  }

  if (on_disconnected_callback_)
    on_disconnected_callback_(status);
}

} // namespace redis
