
#ifndef BPEX_H_
#define BPEX_H_

#include "hiredis/hiredis.h"

// Main class of bpex core.
class Bpex {
public:
  Bpex();
  ~Bpex() = default;

private:
  // Load configuration, setup redis.
  void Initialize();

  void Test(redisReply* reply, int i);

};

#endif  // BPEX_H_