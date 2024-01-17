﻿// SPDX-FileCopyrightText: 2002-2024 PCSX2 Dev Team
// SPDX-License-Identifier: LGPL-3.0+

#pragma once

#include <map>
#include <vector>

#include "Pcsx2Defs.h"

#include "fmt/core.h"

// TODO: Strip down colors, to the handful that are actually used.

enum ConsoleColors
{
	Color_Default = 0,

	Color_Black,
	Color_Green,
	Color_Red,
	Color_Blue,
	Color_Magenta,
	Color_Orange,
	Color_Gray,

	Color_Cyan, // faint visibility, intended for logging PS2/IOP output
	Color_Yellow, // faint visibility, intended for logging PS2/IOP output
	Color_White, // faint visibility, intended for logging PS2/IOP output

	// Strong text *may* result in mis-aligned text in the console, depending on the
	// font and the platform, so use these with caution.
	Color_StrongBlack,
	Color_StrongRed, // intended for errors
	Color_StrongGreen, // intended for infrequent state information
	Color_StrongBlue, // intended for block headings
	Color_StrongMagenta,
	Color_StrongOrange, // intended for warnings
	Color_StrongGray,

	Color_StrongCyan,
	Color_StrongYellow,
	Color_StrongWhite,

	ConsoleColors_Count
};

enum LOGLEVEL
{
	LOGLEVEL_NONE, // Silences all log traffic
	LOGLEVEL_ERROR,
	LOGLEVEL_WARNING,
	LOGLEVEL_INFO,
	LOGLEVEL_DEV,
	LOGLEVEL_DEBUG,
	LOGLEVEL_TRACE,

	LOGLEVEL_COUNT,
};

enum ChannelType
{
	TRACE, LOG
};

/*
 * Adding a Log Channel:
 * To add a log channel, define in the enum, and in the same order define in Channel Meta Data with additional details.
 * Log Channels are under constexpr, and evaluated at compile time.
 */
enum LogChannels
{
	CHANNEL_NONE = 0, // Nothing to log on this channel
	CHANNEL_PCSX2, // General anything PCSX2 without a module
	CHANNEL_SIF,
	CHANNEL_BIOS,
	CHANNEL_CPU,
	CHANNEL_VUM,
	CHANNEL_MEM,
	CHANNEL_CACHE,
	CHANNEL_HW,
	CHANNEL_UNKNOWNHW,
	CHANNEL_DMA,
	CHANNEL_IPU,
	CHANNEL_VIF,
	CHANNEL_SPR,
	CHANNEL_GIF,
	CHANNEL_MSKPATH3,
	CHANNEL_EECNT,
	CHANNEL_VIFCODE,
	CHANNEL_GIFTAG,
	CHANNEL_PSXBIOS,
	CHANNEL_PSXGPU,
	CHANNEL_PSXMEM,
	CHANNEL_PSXHW,
	CHANNEL_PSXUNKNOWNHW,
	CHANNEL_PSXDMA,
	CHANNEL_PSXCNT,
	CHANNEL_MEMCARDS,
	CHANNEL_PAD,
	CHANNEL_GPU,
	CHANNEL_CDVD,
	CHANNEL_MDEC,
	CHANNEL_ELF,
	CHANNEL_EERECPERF,
	CHANNEL_EE,
	CHANNEL_EE_DECI2,
	CHANNEL_IOP,
	CHANNEL_PGIF,
	CHANNEL_RECORDING,
	CHANNEL_CONTROL,
	CHANNEL_MAX
};


struct ChannelMetaData
{
	// Name used to print to console
	std::string_view ChannelName = "UNDEFINED";
	LogChannels Channel;
	std::string_view Category;
	ConsoleColors Color = Color_Default;
	ChannelType Type = ChannelType::LOG;
	int ChannelID = -1;

	std::string GetChannelMenuName()
	{
		std::string result = fmt::format("{}", std::string(ChannelName));
		return result; 
	}
};

constexpr ChannelMetaData ChannelInfo[LogChannels::CHANNEL_MAX]
{
	{"PCSX2",CHANNEL_NONE, "Core", Color_Default, LOG, 0}, // Nothing will log on this channel...
	{"PCSX2",CHANNEL_PCSX2, "Core", Color_Default, LOG, 1}, // General anything PCSX2 without a module

	//Traces
	{"SIF",CHANNEL_SIF,"Core", Color_Default, TRACE, 2},
	{"BIOS",CHANNEL_BIOS, "Core", Color_Default, TRACE, 3},
	{"GPU",CHANNEL_GPU, "Core", Color_Default, TRACE, 4},
	{"VUM",CHANNEL_VUM, "Core", Color_Default, TRACE, 5},
	{"MEM",CHANNEL_MEM, "Core", Color_Default, TRACE, 6},
	{"CACHE",CHANNEL_CACHE, "Core", Color_Default, TRACE, 7},
	{"HW",CHANNEL_HW, "Core", Color_Default, TRACE, 8},
	{"UNKNOWNHW",CHANNEL_UNKNOWNHW, "Core", Color_Default, TRACE, 9},
	{"DMA",CHANNEL_DMA, "PS2", Color_Default, TRACE, 10},
	{"IPU",CHANNEL_IPU, "PS2", Color_Default, TRACE, 11},
	{"VIF",CHANNEL_VIF, "PS2", Color_Default, TRACE, 12},
	{"SPR",CHANNEL_SPR, "PS2", Color_Default, TRACE, 13},
	{"GIF",CHANNEL_GIF, "PS2", Color_Default, TRACE, 14},
	{"MSKPATH3",CHANNEL_MSKPATH3, "PS2", Color_Default, TRACE, 15},
	{"EECNT",CHANNEL_EECNT, "PS2", Color_Default, TRACE, 16},
	{"VIFCODE",CHANNEL_VIFCODE, "PS2", Color_Default, TRACE, 17},
	{"GIFTAG",CHANNEL_GIFTAG, "PS2", Color_Default, TRACE, 18},
	{"PSXBIOS",CHANNEL_PSXBIOS, "PSX", Color_Default, TRACE, 19},
	{"PSXGPU",CHANNEL_PSXGPU, "PSX", Color_Default, TRACE, 20},
	{"PSXMEM",CHANNEL_PSXMEM, "PSX", Color_Default, TRACE, 21},
	{"PSXHW",CHANNEL_PSXHW, "PSX", Color_Default, TRACE, 22},
	{"PSXUNKNOWNHW",CHANNEL_PSXUNKNOWNHW, "PSX", Color_Default, TRACE, 23},
	{"PSXDMA",CHANNEL_PSXDMA, "PSX", Color_Default, TRACE, 24},
	{"PSXCNT",CHANNEL_PSXCNT, "PSX", Color_Default, TRACE, 25},
	{"MEMCARDS",CHANNEL_MEMCARDS, "PSX", Color_Default, TRACE, 26},
	{"PAD",CHANNEL_PAD, "PSX", Color_Default, TRACE, 27},
	{"GPU",CHANNEL_GPU, "PSX", Color_Default, TRACE, 28},
	{"CDVD",CHANNEL_CDVD, "PSX", Color_Default, TRACE, 29},
	{"MDEC",CHANNEL_MDEC, "PSX", Color_Default, TRACE, 30},

	//Logs
	{"ELF",CHANNEL_ELF, "Core", Color_Default, LOG, 31},
	{"EERECPERF",CHANNEL_EERECPERF, "PS2", Color_Default, LOG, 32},
	{"EE",CHANNEL_EE, "PS2", Color_Default, LOG, 33},
	{"EEDECI2",CHANNEL_EE_DECI2, "PS2", Color_Default, LOG, 34},
	{"IOP",CHANNEL_IOP, "PS2", Color_Default, LOG, 35},
	{"PGIF",CHANNEL_PGIF, "PS2", Color_Default, LOG, 36},
	{"RECORDING",CHANNEL_RECORDING, "Core", Color_Default, LOG, 37},
	{"CONTROL",CHANNEL_CONTROL, "Core", Color_Default, LOG, 38}
};

namespace Log
{
	// log message callback type
	using HostCallbackType = void (*)(LOGLEVEL level, ConsoleColors color, std::string_view message);

	// returns the time in seconds since the start of the process
	float GetCurrentMessageTime();

	// returns [L | Timestamp | Channel]
	std::string GetTag();

	std::string GetLogLevelString();
	std::string GetChannelNameString();
	
	// adds a standard console output
	bool IsConsoleOutputEnabled();
	void SetConsoleOutputLevel(LOGLEVEL level);

	// adds a debug console output
	bool IsDebugOutputAvailable();
	bool IsDebugOutputEnabled();
	void SetDebugOutputLevel(LOGLEVEL level);

	// adds a file output
	bool IsFileOutputEnabled();
	bool SetFileOutputLevel(LOGLEVEL level, std::string path);

	// returns the log file, this is really dangerous to use if it changes...
	std::FILE* GetFileLogHandle();

	// adds host output
	bool IsHostOutputEnabled();
	void SetHostOutputLevel(LOGLEVEL level, HostCallbackType callback);

	// sets logging timestamps
	bool AreTimestampsEnabled();
	void SetTimestampsEnabled(bool enabled);

	// Returns the current global filtering level.
	LOGLEVEL GetMaxLevel();

	// writes a message to the log
	void Write(LogChannels channel, LOGLEVEL level, ConsoleColors color, std::string_view message);
	void Writef(LogChannels channel, LOGLEVEL level, ConsoleColors color, const char* format, ...);
	void Writev(LOGLEVEL level, ConsoleColors color, const char* format, va_list ap);
	void WriteFmtArgs(LOGLEVEL level, ConsoleColors color, fmt::string_view fmt, fmt::format_args args);
	
	template <typename... T>
	__fi static void Write(LogChannels channel, LOGLEVEL level, ConsoleColors color, fmt::format_string<T...> fmt, T&&... args)
	{
		// Avoid arg packing if filtered.
		if (level <= GetMaxLevel())
			return WriteFmtArgs(level, color, fmt, fmt::make_format_args(args...));
	}
} // namespace Log