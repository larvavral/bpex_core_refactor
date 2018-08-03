
#include "cpp_redis/cpp_redis"

int main(int argc, const char *argv[]) {
  cpp_redis::client client;

#ifdef DEBUG
  std::cout << "Hi" << std::endl;
#endif

  return 0;
}