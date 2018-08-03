#include "configuration.h"

#include "common/config_file_parser.h"

namespace {

// Configuration file name.
const char kConfigurationFileName[] = "bpex.ini";

}

// static
Configuration* Configuration::GetInstance() {
  // Magic statics.
  static Configuration instance(kConfigurationFileName);
  return &instance;
}

Configuration::Configuration(const std::string& file_name) {
  LoadConfig();
}

void Configuration::LoadConfig() {
  // Use ConfigFileParser to get all settings from configuration file.
}