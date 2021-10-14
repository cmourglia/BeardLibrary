#include <Beard/IO.h>

#if BEARD_PLATFORM_WINDOWS
START_EXTERNAL_INCLUDE
#	include <Windows.h>
END_EXTERNAL_INCLUDE
#elif
#	error TODO
#endif

namespace FileUtils
{
i64 GetFileWriteTime(const char* filename)
{
#if BEARD_PLATFORM_WINDOWS
	HANDLE fileHandle = CreateFileA(filename,
	                                GENERIC_READ,
	                                FILE_SHARE_READ | FILE_SHARE_WRITE,
	                                nullptr,
	                                OPEN_EXISTING,
	                                FILE_ATTRIBUTE_NORMAL,
	                                nullptr);

	Defer(CloseHandle(fileHandle));

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();

		if (error != ERROR_SHARING_VIOLATION) { ASSERT(false, "File error %d", error); }

		return 0;
	}

	FILE_BASIC_INFO infos;

	bool ok = GetFileInformationByHandleEx(fileHandle, FileBasicInfo, &infos, sizeof(infos));
	if (!ok)
	{
		DWORD error = GetLastError();
		ASSERT(false, "File error %d", error);

		return 0;
	}

	return infos.LastWriteTime.QuadPart;
#else
	static_assert(false, "TODO");
#endif
}

std::string ReadWholeFile(const char* filename)
{
	std::string result;
#if BEARD_PLATFORM_WINDOWS
	HANDLE fileHandle = CreateFileA(filename,
	                                GENERIC_READ,
	                                FILE_SHARE_READ | FILE_SHARE_WRITE,
	                                nullptr,
	                                OPEN_EXISTING,
	                                FILE_ATTRIBUTE_NORMAL,
	                                nullptr);

	Defer(CloseHandle(fileHandle));

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();

		if (error != ERROR_SHARING_VIOLATION) { ASSERT(false, "File error %d", error); }

		return result;
	}

	FILE_STANDARD_INFO infos;

	bool ok = GetFileInformationByHandleEx(fileHandle, FileStandardInfo, &infos, sizeof(infos));
	if (!ok)
	{
		DWORD error = GetLastError();
		ASSERT(false, "File error %d", error);

		return result;
	}

	result.resize(infos.EndOfFile.QuadPart);

	DWORD bytesRead = 0;
	ReadFile(fileHandle, result.data(), static_cast<DWORD>(infos.EndOfFile.QuadPart), &bytesRead, nullptr);

#else
	static_assert(false, "TODO");
#endif

	return result;
}

std::optional<std::string> ReadFileIfNewer(const char* filename, i64 lastWrite, i64* newLastWrite)
{
	std::optional<std::string> result;

#if BEARD_PLATFORM_WINDOWS
	HANDLE fileHandle = CreateFileA(filename,
	                                GENERIC_READ,
	                                FILE_SHARE_READ | FILE_SHARE_WRITE,
	                                nullptr,
	                                OPEN_EXISTING,
	                                FILE_ATTRIBUTE_NORMAL,
	                                nullptr);

	Defer(CloseHandle(fileHandle));

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();

		if (error != ERROR_SHARING_VIOLATION) { ASSERT(false, "File error %d", error); }

		return result;
	}

	bool ok = true;

	FILE_BASIC_INFO basicInfos;
	ok = GetFileInformationByHandleEx(fileHandle, FileBasicInfo, &basicInfos, sizeof(basicInfos));
	if (!ok)
	{
		DWORD error = GetLastError();
		ASSERT(false, "File error %d", error);

		return result;
	}

	if (lastWrite >= basicInfos.LastWriteTime.QuadPart) { return result; }

	FILE_STANDARD_INFO standardInfos;
	ok = GetFileInformationByHandleEx(fileHandle, FileStandardInfo, &standardInfos, sizeof(standardInfos));
	if (!ok)
	{
		DWORD error = GetLastError();
		ASSERT(false, "File error %d", error);

		return result;
	}

	if (standardInfos.EndOfFile.QuadPart == 0) { return result; }

	std::string contentTmp;
	DWORD       bytesRead = 0;
	contentTmp.resize(standardInfos.EndOfFile.QuadPart);

	ok = ReadFile(fileHandle,
	              contentTmp.data(),
	              static_cast<DWORD>(standardInfos.EndOfFile.QuadPart),
	              &bytesRead,
	              nullptr);

	if (!ok)
	{
		DWORD error = GetLastError();
		ASSERT(false, "File error %d", error);

		return result;
	}

	*newLastWrite = basicInfos.LastWriteTime.QuadPart;

	result = std::move(contentTmp);
#else
	static_assert(false, "TODO");
#endif

	return result;
}
}