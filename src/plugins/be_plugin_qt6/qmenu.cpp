#include "qmenu.h"
#include "qaction.h"

	// QMENU
		BQMenu::BQMenu()
		: QMenu()
		{
		    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		}

	// PROPERTIES
		bool BQMenu::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				QString s(value);
				if ( s != title() )
				{
					setTitle(tr(value));
					return true;
				}
			}
			return false;
		}

		Bbool BQMenu::onAddChild( BEntity* entity )
		{ 
			auto action = dynamic_cast<BQAction*>(entity);
			if ( action )
			{
				addAction(action);
				return true;
			}
			return false;
		}
