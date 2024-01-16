// SPDX-FileCopyrightText: 2002-2024 PCSX2 Dev Team
// SPDX-License-Identifier: LGPL-3.0+

#include "common/Console.h"

// Dummy objects, need to get rid of them...
ConsoleLogWriter<LOGLEVEL_INFO> Console;
ConsoleLogWriter<LOGLEVEL_DEV> DevCon;

#ifdef _DEBUG
ConsoleLogWriter<LOGLEVEL_DEBUG> DbgConWriter;
#else
NullLogWriter DbgConWriter;
#endif
