#include "common/string_helper.h"

#include <algorithm>

namespace common {

std::vector<std::string> Split(const std::string& s, wchar_t delim) {
  std::vector<std::string> ret;
  std::size_t curr = s.find(delim);
  std::size_t prev = 0;

  while (curr != std::string::npos) {
    ret.push_back(s.substr(prev, curr - prev));
    prev = curr + 1;
    curr = s.find(delim, prev);
  }
  ret.push_back(s.substr(prev, curr - prev));

  return ret;
}

std::string Trim(const std::string &s) {
  auto const is_space = [](int c) {
    return std::isspace(c);
  };

  auto wsfront = std::find_if_not(s.begin(), s.end(), is_space);
  auto wsback = std::find_if_not(s.rbegin(), s.rend(), is_space).base();
  return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

} // namespace common