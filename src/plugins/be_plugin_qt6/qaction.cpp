#include "qaction.h"
#include <iostream>

	// QMENU
		BQAction::BQAction()
		: QAction()
		{
			connect(this, &BQAction::triggered, this, &BQAction::commit);
		}

	// PROPERTIES
		bool BQAction::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				QString s(value);
				if ( s != text() )
				{
					setText(tr(value));
					onUpdate();
					return true;
				}
			}
			return false;
		}

		void BQAction::commit()
		{
			dynamic_cast<BEntity_trigger*>(this)->set();
		}
