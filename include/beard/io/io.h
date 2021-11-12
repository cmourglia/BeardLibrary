#pragma once

#include <beard/core/macros.h>

// TODO: Remove dependency to STL
#include <optional>
#include <string>

namespace beard::io
{
i64 get_file_write_time(const char* filename);

std::string read_whole_file(const char* filename);

std::optional<std::string> read_while_file_if_newer(const char* filename, i64 last_write, i64* write_time);
}