#include "configuration.h"

#include "common/config_file_parser.h"
#include "configuration_key.h"

namespace {

// Configuration file name.
const char kConfigurationFileName[] = "bpex.ini";

}

// static
Configuration* Configuration::GetInstance() {
  // Magic statics.
  static Configuration instance;
  return &instance;
}

Configuration::Configuration() {
  LoadConfig(kConfigurationFileName);
}

void Configuration::LoadConfig(const std::string& file_name) {
  // Use ConfigFileParser to get all settings from configuration file.
  common::ConfigFileParser config_file_parser(file_name);

  redis_server_.ip = config_file_parser.GetValue(kRedisServerIp);
  redis_server_.port = config_file_parser.GetInt(kRedisServerPort);
  redis_server_.password = config_file_parser.GetValue(kRedisServerPassword);
}

RedisServerInformation Configuration::GetRedisServerInfo() {
  return redis_server_;
}