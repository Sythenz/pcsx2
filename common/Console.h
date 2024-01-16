// SPDX-FileCopyrightText: 2002-2024 PCSX2 Dev Team
// SPDX-License-Identifier: LGPL-3.0+

#pragma once

#include "Pcsx2Defs.h"

#include "fmt/core.h"

#include <cstdarg>
#include <string>

#include "log.h"

// TODO: Nuke this - namespace for log moved to log.h/cpp - Console.h/cpp is now just a wrapper to handle old code.
// Do not remove until all console call sites are replaced.

// Adapter classes to handle old code.
template <LOGLEVEL level>
struct ConsoleLogWriter
{
	__fi static void Error(std::string_view str) { Log::Write(CHANNEL_PCSX2, level, Color_StrongRed, str); }
	__fi static void Warning(std::string_view str) { Log::Write(CHANNEL_PCSX2, level, Color_StrongOrange, str); }
	__fi static void WriteLn(std::string_view str) { Log::Write(CHANNEL_PCSX2, level, Color_Default, str); }
	__fi static void WriteLn(ConsoleColors color, std::string_view str) { Log::Write(CHANNEL_PCSX2, level, color, str); }
	__fi static void WriteLn() { Log::Write(CHANNEL_PCSX2, level, Color_Default, std::string_view()); }
	__fi static void FormatV(const char* format, va_list ap) { Log::Writev(level, Color_Default, format, ap); }
	__fi static void FormatV(ConsoleColors color, const char* format, va_list ap) { Log::Writev(level, color, format, ap); }

#define MAKE_PRINTF_CONSOLE_WRITER(color) \
	do \
	{ \
		std::va_list ap; \
		va_start(ap, format); \
		Log::Writev(level, color, format, ap); \
		va_end(ap); \
	} while (0)

	// clang-format off
	__fi static void Error(const char* format, ...) { MAKE_PRINTF_CONSOLE_WRITER(Color_StrongRed); }
	__fi static void Warning(const char* format, ...) { MAKE_PRINTF_CONSOLE_WRITER(Color_StrongOrange); }
	__fi static void WriteLn(const char* format, ...) { MAKE_PRINTF_CONSOLE_WRITER(Color_Default); }
	__fi static void WriteLn(ConsoleColors color, const char* format, ...) { MAKE_PRINTF_CONSOLE_WRITER(color); }
	// clang-format on	

#undef MAKE_PRINTF_CONSOLE_WRITER

#define MAKE_FMT_CONSOLE_WRITER(color) do \
	{ \
		if (level <= Log::GetMaxLevel()) \
			Log::WriteFmtArgs(level, color, fmt, fmt::make_format_args(args...)); \
} \
	while (0)

	// clang-format off
	template<typename... T> __fi static void ErrorFmt(fmt::format_string<T...> fmt, T&&... args) { MAKE_FMT_CONSOLE_WRITER(Color_StrongRed); }
	template<typename... T> __fi static void WarningFmt(fmt::format_string<T...> fmt, T&&... args) { MAKE_FMT_CONSOLE_WRITER(Color_StrongOrange); }
	template<typename... T> __fi static void WriteLnFmt(fmt::format_string<T...> fmt, T&&... args) { MAKE_FMT_CONSOLE_WRITER(Color_Default); }
	template<typename... T> __fi static void WriteLnFmt(ConsoleColors color, fmt::format_string<T...> fmt, T&&... args) { MAKE_FMT_CONSOLE_WRITER(color); }
	// clang-format on

#undef MAKE_FMT_CONSOLE_WRITER
};

struct NullLogWriter
{
	// clang-format off
	__fi static bool Error(std::string_view str) { return false; }
	__fi static bool Warning(std::string_view str) { return false; }
	__fi static bool WriteLn(std::string_view str) { return false; }
	__fi static bool WriteLn(ConsoleColors color, std::string_view str) { return false; }
	__fi static bool WriteLn() { return false; }

	__fi static bool Error(const char* format, ...) { return false; }
	__fi static bool Warning(const char* format, ...) { return false; }
	__fi static bool WriteLn(const char* format, ...) { return false; }
	__fi static bool WriteLn(ConsoleColors color, const char* format, ...) { return false; }

	template<typename... T> __fi static bool ErrorFmt(fmt::format_string<T...> fmt, T&&... args) { return false; }
	template<typename... T> __fi static bool WarningFmt(fmt::format_string<T...> fmt, T&&... args) { return false; }
	template<typename... T> __fi static bool WriteLnFmt(fmt::format_string<T...> fmt, T&&... args) { return false; }
	template<typename... T> __fi static bool WriteLnFmt(ConsoleColors color, fmt::format_string<T...> fmt, T&&... args) { return false; }
	// clang-format on	
};

extern ConsoleLogWriter<LOGLEVEL_INFO> Console;
extern ConsoleLogWriter<LOGLEVEL_DEV> DevCon;

#ifdef _DEBUG
extern ConsoleLogWriter<LOGLEVEL_DEBUG> DbgConWriter;
#define DbgCon DbgConWriter
#else
extern NullLogWriter DbgConWriter;
#define DbgCon 0 && DbgConWriter
#endif
