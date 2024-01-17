#include "PrecompiledHeader.h"
#include "LoggingMenu.h"

#include "common/log.h"
#include "DebugTools/Debug.h"

LOG_SETCHANNEL(CHANNEL_PCSX2)

LoggingMenu::LoggingMenu(QMenu* parent)
{
	this->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	loggingmenu = parent->addMenu(tr("Logging"));
	tracemenu = parent->addMenu(tr("Traces"));
	
	GetChannelCategories();
	RegenerateMenus();
}

QMenu* LoggingMenu::GenerateMenu(QMenu* inMenu, ChannelType inType)
{

	for(std::string_view category : categories)
	{
		QMenu* categorymenu = inMenu->addMenu(tr(std::string(category).c_str()));
		
		QAction* DisableLoggingAction = new QAction(tr("Disable All"), categorymenu);
		DisableLoggingAction->setCheckable(true);
		DisableLoggingAction->setChecked(false);
		categorymenu->addAction(DisableLoggingAction);
		connect(DisableLoggingAction, &QAction::triggered, this, [this]() {  });

		categorymenu->addSeparator();
		
		for(ChannelMetaData Channel : ChannelInfo)
		{
			if(Channel.Category == category && Channel.Type == inType)
			{
				QAction* newAction = new QAction(tr(Channel.GetChannelMenuName().c_str()),categorymenu);
				newAction->setCheckable(true);
				categorymenu->addAction(newAction);
				connect(newAction, &QAction::triggered, this, [this]() {  });
			}
		}
	}
 
	return inMenu;
}

std::set<std::string_view> LoggingMenu::GetChannelCategories()
{
	LOG_INFO("Accumulating log channels...");
	
	for(ChannelMetaData Channel : ChannelInfo)
	{
		categories.insert(Channel.Category);
	}
	
	return categories;
}


void LoggingMenu::RegenerateMenus()
{
	GenerateMenu(loggingmenu, ChannelType::LOG);

#if defined(PCSX2_DEBUG) || defined(PCSX2_DEVBUILD)
	GenerateMenu(tracemenu, ChannelType::TRACE);
#endif

}
