// SPDX-FileCopyrightText: 2002-2023 PCSX2 Dev Team
// SPDX-License-Identifier: LGPL-3.0+

#pragma once
#include <set>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

#include "AboutDialog.h"
#include "common/log.h"

class LoggingDialog final : public QDialog
{
	Q_OBJECT
	
public:
	explicit LoggingDialog(QWidget* parent = nullptr);
	~LoggingDialog();

private:
	
	//Ui::LoggingDialog m_ui;
};

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
