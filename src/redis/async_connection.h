#ifndef REDIS_ASYNC_CONNECTION_H_
#define REDIS_ASYNC_CONNECTION_H_

#include <functional>
#include <string>

#include "hiredis/adapters/libevent.h"

namespace redis {

class AsyncConnection {
public:
  typedef std::function<void(int)> ConnectCallback;
  typedef std::function<void(std::string)> ExecuteCommandCallback;

  AsyncConnection(const std::string& host, int port);
  ~AsyncConnection();

  // Connect to redis server.
  void Connect();

  // Check whether redis client is connected or not.
  bool IsConnected();

  // Disconnect to redis server.
  void Disconnect();

  // // Authenticate in case password is required.
  // void Authenticate(const std::string& password);

  // // Invoked when received authenticate response from redis server.
  // void OnAuthenticated(redisReply* reply);

  // Set callback, which is invoked when connected to redis server.
  void SetOnConnectedCallback(ConnectCallback cb) {
    on_connected_callback_ = cb;
  }

  // Set callback, which is invoked when disconnected to redis server.
  void SetOnDisconnectedCallback(ConnectCallback cb) {
    on_disconnected_callback_ = cb;
  }

    // TODO(hoangpq): Currently just support pass reply to callback.
  // Please improve by add previous data to callback.
  // void ExecuteAsyncCommand(
  //     const std::string& command, ExecuteCommandCallback cb);
  template<typename ExecuteHandler>
  void ExecuteAsyncCommand(const std::string& command, ExecuteHandler handler) {
    if (!IsConnected())
      return;

    Handler<ExecuteHandler> *hd = new Handler<ExecuteHandler>(handler);
    int result = redisAsyncCommand(async_context_,
                                   Handler<ExecuteHandler>::Callback,
                                   hd,
                                   command.c_str());
    if (result == REDIS_ERR) {
      // Remember to delete Handle to avoid memory leak.
      // In case of successful command, handle is deleted by itself.
      delete hd;
    }
  }

private:
  // Helper class which are used to handle callback when execute async command.
  template<typename CallbackT>
  class Handler {
  public:
    Handler(CallbackT cb) : callback_(cb) {}

    static void Callback(redisAsyncContext* ac, void* reply, void* privdata) {
      throw std::invalid_argument("AAA");
      (static_cast<Handler<CallbackT>*>(privdata))->operator()(ac, reply);
    }

    void operator()(redisAsyncContext* ac, void* reply) {
      // if (reply) {
      //   callback_(static_cast<redisReply*>(reply));
      // }
      callback_(static_cast<redisReply*>(reply));
      delete(this);
    }

  private:
    CallbackT callback_;
  };

  // Use static function to set callback to hiredis.
  static void Connected(const redisAsyncContext* ac, int status);
  static void Disconnected(const redisAsyncContext* ac, int status);

  // Actual connection callback functions.
  void OnConnected(int status);
  void OnDisconnected(int status);

  std::string host_;
  int port_;

public:
  redisAsyncContext* async_context_;

  ConnectCallback on_connected_callback_;
  ConnectCallback on_disconnected_callback_;
};

} // namespace redis

#endif  // REDIS_ASYNC_CONNECTION_H_
