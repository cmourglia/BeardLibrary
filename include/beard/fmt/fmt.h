#pragma once

#include <charconv>
#include <optional>
#include <string_view>
#include <vector>

#include "beard/misc/optional.h"

namespace beard::fmt {
std::vector<std::string_view> tokenize(std::string_view input,
                                       std::string_view token,
                                       bool skip_empty = true) {
  std::vector<std::string_view> result;

  auto curr_str = input;
  usize offset;
  while ((offset = curr_str.find_first_of(token)) != std::string_view::npos) {
    if (offset != 0 || !skip_empty) {
      result.push_back(curr_str.substr(0, offset));
    }
    curr_str = curr_str.substr(offset + 1);
  }

  if (!curr_str.empty()) {
    result.push_back(curr_str);
  }

  return result;
}

template <typename T>
inline beard::optional<T> parse_number(std::string_view input) {
  T result;
  auto start = input.data();
  auto end = input.data() + input.size();
  auto parse_result = std::from_chars(start, end, result);

  if (parse_result.ec != std::errc{}) {
    return {};
  }

  return result;
}

}  // namespace beard::fmt