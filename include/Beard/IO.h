#pragma once

#include <Beard/Macros.h>

// TODO: Remove dependency to STL
#include <optional>
#include <string>

namespace Beard
{
namespace IO
{
	i64 GetFileWriteTime(const char* filename);

	std::string ReadWholeFile(const char* filename);

	std::optional<std::string> ReadWholeFileIfNewer(const char* filename, i64 last_write, i64* write_time);

}
}