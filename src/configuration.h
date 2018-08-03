#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

namespace {

struct RedisServerInformation {
  std::string ip;
  std::string port;
  std::string password;
};

}

// This class contains all settings of this application.
// It's a singleton.
class Configuration {
public:
  static Configuration* GetInstance();

  // Delete these 2 functions to make sure not get copies of this
  // singleton accidentally.
  Configuration(Configuration const&) = delete;
  void operator=(Configuration const&) = delete;

  // Get configuration.
  RedisServerInformation GetRedisServerInfo();

private:
  // Private instance to avoid instancing.
  Configuration();
  ~Configuration() = default;

  RedisServerInformation redis_server_;

  // Load all settings from config file.
  void LoadConfig(const std::string& file_name);
};

#endif  // CONFIGURATION_H_