
#ifndef COMMON_CONFIG_FILE_PARSER_H_
#define COMMON_CONFIG_FILE_PARSER_H_

#include <map>

// This class used to support reading configuration from file.
class ConfigFileParser {
public:
  ConfigFileParser();
  ConfigFileParser(const std::string& file_name);
  ~ConfigFileParser();

  // Read all settings from config file.
  void ReadFromFile(const std::string& file_name);

  // Parse and get data.
  std::string GetValue(const std::string& key);
  int GetInt(const std::string& key);
  double GetDouble(const std::string& key);

private:
  std::map<std::string, std::string> data_;
};

#endif  // COMMON_CONFIG_FILE_PARSER_H_