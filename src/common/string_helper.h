
#ifndef COMMON_STRING_HELPER_H_
#define COMMON_STRING_HELPER_H_

#include <string>
#include <vector>

namespace common {

// Split string.
std::vector<std::string> Split(const std::string& s, wchar_t delim = L' ');

// Trim from both start and end of string.
std::string Trim(const std::string &s);

} // namespace common

#endif  // COMMON_STRING_HELPER_H_