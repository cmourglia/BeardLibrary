#include "beard/io/io.h"

#include <codecvt>
#include <cstdio>
#include <filesystem>

#include "beard/core/macros.h"

namespace beard::io {
i64 file_write_time(std::string_view filename) {
  namespace fs = std::filesystem;
  auto write_time = fs::last_write_time(fs::path{filename});
  return write_time.time_since_epoch().count();
}

std::string read_whole_file(std::string_view filename) {
  FILE* file = fopen(filename.data(), "rb");
  if (file == nullptr) {
    return "";
  }

  defer(fclose(file));

  fseek(file, SEEK_END, SEEK_SET);
  auto length = ftell(file);
  rewind(file);

  std::string result;
  result.resize(length);

  auto read_len = fread(result.data(), sizeof(char), length, file);
  ASSERT(read_len == length, "Read less bytes than the length of the file");
  UNUSED(read_len);

  return result;
}

beard::optional<std::string> read_whole_file_if_newer(std::string_view filename,
                                                      i64 last_write,
                                                      i64* new_last_write) {
  beard::optional<std::string> result;

  auto current_write_time = file_write_time(filename);

  if (current_write_time > last_write) {
    result = read_whole_file(filename);
    *new_last_write = current_write_time;
  }

  return result;
}

// std::u32string to_utf8(const std::string& str) {
//   std::wstring_convert<std::codecvt_utf8<i32>, i32> converter;
//
//   auto as_int = converter.from_bytes(str);
//   return {reinterpret_cast<char32_t const*>(as_int.data()), as_int.length()};
// }
//
// std::string from_utf8(const std::u32string& str) {
//   std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
//
//   auto as_char = converter.to_bytes(str);
//   return {reinterpret_cast<char const*>(as_char.data(), as_char.length())};
// }
}  // namespace beard::io