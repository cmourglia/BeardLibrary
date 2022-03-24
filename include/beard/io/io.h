#pragma once

#include <string>
#include <string_view>

#include "beard/core/macros.h"
#include "beard/misc/optional.h"

namespace beard::io {
i64 get_file_write_time(std::string_view filename);

std::string read_whole_file(std::string_view filename);

beard::optional<std::string> read_while_file_if_newer(std::string_view filename,
                                                      i64 last_write,
                                                      i64* write_time);

// std::u32string to_utf8(const std::string& str);
// std::string from_utf8(const std::u32string& str);
}  // namespace beard::io