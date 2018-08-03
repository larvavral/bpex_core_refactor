
#ifndef BPEX_H_
#define BPEX_H_

// Main class of bpex core.
class Bpex {
public:
  Bpex();
  ~Bpex() = default;

private:
  // Load configuration, setup redis.
  void Initialize();

};

#endif  // BPEX_H_