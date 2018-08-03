#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

// This class contains all settings of this application.
// It's a singleton.
class Configuration {
public:
  static Configuration* GetInstance();

  // Delete these 2 functions to make sure not get copies of this
  // singleton accidentally.
  Configuration(Configuration const&) = delete;
  void operator=(Configuration const&) = delete;
private:
  // Private instance to avoid instancing.
  Configuration(const std::string& file_name);
  ~Configuration() = default;

  // Load all setting from config file.
  void LoadConfig();
};

#endif  // CONFIGURATION_H_