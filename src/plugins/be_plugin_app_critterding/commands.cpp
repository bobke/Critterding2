#include "commands.h"
 
	bool cmd_launchAdminWindow::set()
	{
		if ( !getAdminWindow() )
		{
			auto qt_app = topParent()->getChild( "Scene", 1 )->getChild( "QT Application", 2 );
			if ( qt_app )
			{
				qt_app->addChild( "Admin App", "AdminWindow" );
				return true;
			}
		}
		return false;
	}

	bool cmd_launchControlPanel::set()
	{
		auto qt_app = topParent()->getChild( "Scene", 1 )->getChild( "QT Application", 2 );
		if ( qt_app )
		{
			if ( !qt_app->getChild( "CdControlPanel", 1 ) )
			{
				qt_app->addChild( "CdControlPanel", "CdControlPanel" );
			}
			return true;
		}
		return false;
	}
