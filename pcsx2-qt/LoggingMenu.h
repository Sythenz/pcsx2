// SPDX-FileCopyrightText: 2002-2023 PCSX2 Dev Team
// SPDX-License-Identifier: LGPL-3.0+

#pragma once
#include <set>
#include <QtWidgets/QMenu>

#include "common/log.h"

class LoggingMenu final : public QMenu
{
	Q_OBJECT

public:
	
	explicit LoggingMenu(QMenu* parent);

	void RegenerateMenus();

private:
	QMenu* GenerateMenu(QMenu* inMenu, ChannelType inType);
	
	std::set<std::string_view> GetChannelCategories();
	
	QMenu* loggingmenu;
	QMenu* tracemenu;

	std::set<std::string_view> categories;
};
