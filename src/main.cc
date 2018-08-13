#include <iostream>

#include "bpex.h"
#include "signal.h"
#include "hiredis/adapters/libevent.h"

struct event_base *base;

void haha(redisAsyncContext* ac, void* reply, void* privdata) {
  std::cout << "callbacked" << std::endl;
}

int main(int argc, const char *argv[]) {
  signal(SIGPIPE, SIG_IGN);
  base = event_base_new();


  redisAsyncContext* ac = redisAsyncConnect("172.16.20.167", 6379);
  if (ac->err) {
    std::cout << "Err" << std::endl;
  }

  std::cout << "Connected" << std::endl;
  redisLibeventAttach(ac,base);

  redisAsyncCommand(ac, haha, (char*)"auth", "AUTH %s", "liquid109");

  // Bpex bpex_app;
  while (true) ;

  return 0;
}